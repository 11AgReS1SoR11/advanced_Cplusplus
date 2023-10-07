#include "Calculator.hpp"

#include <stack>
#include <charconv>
#include <iostream>

double Calculator::operator()(std::string_view expression) const
{
    auto const tokenz = parser(expression);
    auto const sorted_tokenz = sorter(tokenz);
    std::stack<double> operands{};
    double result = 0;
    for (auto const token : sorted_tokenz)
    {
        std::cout << "token: " << token << std::endl;
        if (sorter.IsAlNum(token))
        {
            double number = 0;
            std::from_chars(token.data(), token.data() + token.size(), number);
            std::cout << "num: " << number << std::endl;
            operands.push(number);
        } 
        else 
        {
            double operand2 = operands.top();
            operands.pop();
            std::cout << "operands: " << operand2 << std::endl;

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
