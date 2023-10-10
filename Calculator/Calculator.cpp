#include "Calculator.hpp"

#include "plugins/funcsin.hpp"
#include "plugins/funccos.hpp"
#include "plugins/funcpow.hpp"

#include <stack>
#include <charconv>

double Calculator::operator()(std::string_view expression)
{
    logger << "Expression: " << expression;
    logger << "Parsing expression";
    auto const tokenz = parser(expression);

    logger << "Infix to RPN";
    auto const sorted_tokenz = sorter(tokenz);

    logger << "Start calculating";
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
                logger << "Loading function: " << "Pow" << " from" << "plugins/libfuncpow.so";
                auto Pow = loader.loadFunction<double(double, double)>("plugins/libfuncpow.so", "Pow");

                double operand1 = operands.top();
                operands.pop();
                operands.push(Pow(operand1, operand2));
            } else if (token == "sin") {
                logger << "Loading function: " << "Sin" << " from" << "plugins/libfuncsin.so";
    
                auto Sin = loader.loadFunction<double(double)>("plugins/libfuncsin.so", "Sin");
                operands.push(Sin(operand2));
            } else if (token == "cos") {
                logger << "Loading function: " << "Cos" << " from" << "plugins/libfunccos.so";

                auto Cos = loader.loadFunction<double(double)>("plugins/libfunccos.so", "Cos");
                operands.push(Cos(operand2));
            } else {
                throw std::runtime_error("Incorect enter: " + std::string(token.data()));
            }
        }
    }

    logger << "Calculator successfully calculates";
    return operands.top();
}
