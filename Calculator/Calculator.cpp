#include "Calculator.hpp"

#include "plugins/funcsin.hpp"
#include "plugins/funccos.hpp"
#include "plugins/funcpow.hpp"

#include <stack>
#include <charconv>

double Calculator::operator()(std::string_view expression)
{
    auto const tokenz = parser(expression);
    auto const sorted_tokenz = sorter(tokenz);
    std::stack<double> operands{};
    for (auto const token : sorted_tokenz)
    {
        if (sorter.IsAlNum(token))
        {
            double number = 0;
            std::from_chars(token.data(), token.data() + token.size(), number);
            operands.push(number);
        } 
        else 
        {
            double operand2 = operands.top();
            operands.pop();

            if (token == "+") {
                double operand1 = operands.top();
                operands.pop();
                operands.push(operand1 + operand2);
            } else if (token == "-") {
                double operand1 = operands.top();
                operands.pop();
                operands.push(operand1 - operand2);
            } else if (token == "*") {
                double operand1 = operands.top();
                operands.pop();
                operands.push(operand1 * operand2);
            } else if (token == "/") {
                double operand1 = operands.top();
                operands.pop();
                if (operand2 == 0)
                    throw std::runtime_error("division by 0");
                operands.push(operand1 / operand2);
            } else if (token == "^") {
                auto Pow = loader.loadFunction<double(double, double)>("plugins/libfuncpow.so", "Pow");

                double operand1 = operands.top();
                operands.pop();
                operands.push(Pow(operand1, operand2));
            } else if (token == "sin") {
                auto Sin = loader.loadFunction<double(double)>("plugins/libfuncsin.so", "Sin");
                operands.push(Sin(operand2));
            } else if (token == "cos") {
                auto Cos = loader.loadFunction<double(double)>("plugins/libfunccos.so", "Cos");
                operands.push(Cos(operand2));
            } else {
                throw std::runtime_error("Incorect enter: " + std::string(token.data()));
            }
        }
    }

    return operands.top();
}
