#include "Parser.hpp"

#include <stack>
#include <stdexcept>

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
    int last_token_idx = -1;
    std::string_view token{};

    for (long unsigned int idx = 0; idx < expression.size(); ++idx)
    {
        if (isbinaryminus(expression, idx) || isoperator(expression[idx]))
        {
            // add prev operand
            token = std::string_view{expression.data() + last_token_idx + 1, idx - last_token_idx - 1};
            if (!token.empty()) { tokens.push_back(token); }
            // add operator
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
    token = std::string_view{expression.data() + last_token_idx + 1, expression.size() - (last_token_idx + 1)};
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

bool Parser::isoperator(const char c) const
{
    if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    return false;
}
