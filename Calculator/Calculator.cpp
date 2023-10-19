#include "Calculator.hpp"

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
                logger << "Loading function: " << "^";
                auto Pow = loader.loadFunction<double(double, double)>("pow");

                double operand1 = operands.top();
                operands.pop();
                operands.push(Pow(operand1, operand2));
            } else if (token == "sin") {
                logger << "Loading function: " << token;
    
                auto Func = loader.loadFunction<double(double)>("sin");
                operands.push(Func(operand2));
            } else if (token == "cos") {
                logger << "Loading function: " << token;
    
                auto Func = loader.loadFunction<double(double)>("cos");
                operands.push(Func(operand2));
            } else {
                throw std::runtime_error("Undefined function");
            }
        }
    }

    logger << "Calculator successfully calculates";
    double ans = operands.top(); 
    return ans;
}
