#include "Parser.hpp"

#include <stack>
#include <stdexcept>
#include <iostream>

std::vector<std::string_view> Parser::operator()(std::string_view expression) const
{
    сheck_bracket_sequence(expression);
    return tokenize(expression);
}

void Parser::сheck_bracket_sequence(std::string_view expression) const
{
    std::stack<char> S;
    for (char c : expression) 
    {
        if (c == '(' || c == '[') 
        {
            S.push(c);
        } 
        else if (c == ')' || c == ']') 
        {
            if (S.empty()) 
            {
                throw std::runtime_error("Wrong expression (check brackets)");
            }

            char top = S.top();
            S.pop();

            if ((c == ')' && top != '(') || (c == ']' && top != '[')) 
            {
                throw std::runtime_error("Wrong expression (check brackets)");
            }
        }
    }

    if (!S.empty())
    {
        throw std::runtime_error("Wrong expression (check brackets)");
    }
}

std::vector<std::string_view> Parser::tokenize(std::string_view expression) const
{
    std::vector<std::string_view> tokens{};
    long unsigned int last_token_idx = 0;
    std::string_view token{};

    for (long unsigned int idx = 0; idx < expression.size(); ++idx)
    {
        // while don't work for inner brackets
        if (expression[idx] == '(')
        {
            last_token_idx = expression.find(')', idx);

            // add '('
            token = std::string_view{expression.data() + idx, 1}; 
            tokens.push_back(token);

            // add between '(' and ')'
            token = std::string_view{expression.data() + idx + 1, last_token_idx - idx - 1}; 
            auto inner_tokens = tokenize(token);
            for (auto inner_token : inner_tokens)
            {
                tokens.push_back(inner_token);
            }

            // add ')'
            token = std::string_view{expression.data() + last_token_idx, 1}; 
            tokens.push_back(token);

            idx = last_token_idx;
        }
        else if (expression[idx] == '+' || expression[idx] == '*' || expression[idx] == '/' || isbinaryminus(expression, idx) || expression[idx] == '^')
        {
            // add prev operand
            if (last_token_idx != idx)
            {
                if (last_token_idx == 0) // some problems with first token
                {
                    token = std::string_view{expression.data(), idx};
                }
                else
                {
                    token = std::string_view{expression.data() + last_token_idx + 1, idx - last_token_idx - 1};
                }
                if (!token.empty()) { tokens.push_back(token); }
            }
            // add operand
            token = std::string_view{expression.data() + idx, 1};
            tokens.push_back(token);

            last_token_idx = idx;
        }
        else if (idx + 3 <= expression.size() && isfunc({expression.data() + idx, 3})) // a little bit hardcode, but for sin and cos norm
        {
            // add func
            token = std::string_view{expression.data() + idx, 3};
            last_token_idx = idx += 2;

            tokens.push_back(token);
        }
    }

    // add last token
    token = std::string_view{expression.data() + (last_token_idx ? last_token_idx + 1 : 0), expression.size() - (last_token_idx ? last_token_idx + 1 : 0)};
    if (!token.empty()) { tokens.push_back(token); }

    return tokens;
}

bool Parser::isfunc(std::string_view str) const
{
    if (str.size() >= 3 && 
        (str[0] == 's' && str[1] == 'i' && str[2] == 'n' ||
        str[0] == 'c' && str[1] == 'o' && str[2] == 's'))
    {
        return true;
    }
    return false;
}

bool Parser::isbinaryminus(std::string_view expression, int const idx) const
{
    if (expression[idx] == '-' && !((idx > 0 && expression[idx-1] == '(') || idx == 0)) // unary minus [only after '(']
    {
        return true;
    }
    return false;
}
