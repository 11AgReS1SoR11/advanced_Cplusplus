#include "Sorter.hpp"
#include <iostream>
#include <stack>

std::vector<std::string_view> Sorter::operator()(const std::vector<std::string_view> words) const
{
    std::vector<std::string_view> res{};
    std::stack<std::string_view> stack{};
    // for (auto m : words)
    // {
    //     std::cout << m << " " << words.size() << std::endl;
    // }
    for (auto const expression : words)
    {
        // std::cout << "Provirka : " << expression << " size = " << res.size() << " " << stack.size() << std::endl;
        // for (auto m : res)
        // {
        //     std::cout << m << std::endl;
        // }
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
        // for (auto m : priorities)
        // {
        //     std::cout << m.first << " " << m.second << " size = " << priorities.size() << std::endl;
        // }
    }
    // std::cout << "Provirka last: " << res.size() << std::endl;

    while (!stack.empty())
    {
        res.push_back(stack.top());
        stack.pop();
    }

    // std::cout << "Provirka last: " << res.size() << std::endl;
    // for (auto m : res)
    // {
    //     std::cout << m << std::endl;
    // }
    // std::cout << "end last: " << std::endl;

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