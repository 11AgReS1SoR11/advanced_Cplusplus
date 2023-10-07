#include "Calculator.hpp"

#include <stack>
#include <charconv>
#include <cmath>

double Calculator::operator()(std::string_view expression) const
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
                operands.push(operand1 / operand2);
            } else if (token == "^") {
                double operand1 = operands.top();
                operands.pop();
                operands.push(std::pow(operand1, operand2));
            } else if (token == "sin") {
                operands.push(std::sin(operand2));
            } else if (token == "cos") {
                operands.push(std::cos(operand2));
            }
        }
    }

    return operands.top();
}
