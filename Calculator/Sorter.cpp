#include "Sorter.hpp"

#include <unordered_map>
#include <stack>

std::vector<std::string_view> Sorter::operator()(std::vector<std::string_view> words) const
{
    std::unordered_map<std::string_view, size_t> map = { // сделать constexpr
        {"+", 2},
        {"-", 2},
        {"*", 3},
        {"/", 3}
    };

    std::vector<std::string_view> res{words.size()};
    std::stack<std::string_view> stack{};
    for (auto expression : words)
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
        else if (stack.empty() || (map[stack.top()] < map[expression]))
        {
            stack.push(expression);
        }
        else
        {
            do
            {
                res.push_back(stack.top());
                stack.pop();
            } while (!(stack.empty() || (map[stack.top()] < map[expression])));
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

bool Sorter::IsAlNum(std::string_view str) const
{
    for (auto c : str)
    {
        if (!(std::isdigit(c) || c == '.'))
        {
            return false;
        }
    }
    return true;
}