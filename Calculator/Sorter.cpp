#include "Sorter.hpp"

#include <stack>
#include <cctype>

std::vector<std::string_view> Sorter::operator()(const std::vector<std::string_view> words) const noexcept
{
    std::vector<std::string_view> res{};
    std::stack<std::string_view> stack{};
    for (auto const expression : words)
    {
        if (IsAlNum(expression))
        {
            res.push_back(expression);
        }
        else if (expression == ")")
        {
            while (stack.top() != "(")
            {
                res.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else if (expression == "(")
        {
            stack.push(expression);
        }
        else if (stack.empty() || (priorities.at(stack.top()) < priorities.at(expression)))
        {
            stack.push(expression);
        }
        else
        {
            do
            {
                res.push_back(stack.top());
                stack.pop();
            } while (!(stack.empty() || (priorities.at(stack.top()) < priorities.at(expression))));
            stack.push(expression);
        }
    }

    while (!stack.empty())
    {
        res.push_back(stack.top());
        stack.pop();
    }

    return res;
}

bool Sorter::IsAlNum(std::string_view str) const noexcept
{
    if (str.empty()) return false;
    bool have_dot = false;
    for (auto const c : str)
    {
        if (!std::isdigit(c))
        {
            if (c == '.' && have_dot)
            {
                return false;
            }
            else if (c == '.')
            {
                have_dot = true;
            }
            else if (str[0] != '-' || str.size() <= 1)
            {
                return false;
            }
        }
    }
    return true;
}