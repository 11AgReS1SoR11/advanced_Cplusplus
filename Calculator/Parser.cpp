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
    for (int idx = 0; idx < expression.size(); ++idx) 
    {
		if (expression[idx] == '(' || expression[idx] == '[') 
        {
			S.push(expression[idx]);
		}
		if ((expression[idx] == ')' || expression[idx] == ']') && (S.empty())) 
        {
			throw std::runtime_error("Wrong expression (check brackets)");
		}
		if ((expression[idx] == ')' && S.top() == '(') || (expression[idx] == ']' && S.top() == '[')) 
        {
			S.pop();
		}
		else if ((expression[idx] == ')' && S.top() != '(') || (expression[idx] == ']' && S.top() != '[')) 
        {
			throw std::runtime_error("Wrong expression (check brackets)");
		}
	}
}

std::vector<std::string_view> Parser::tokenize(std::string_view expression) const
{
    std::vector<std::string_view> tokens{};
    long unsigned int last_token_idx = 0;
    std::string_view token{};

    for (int idx = 0; idx < expression.size(); ++idx)
    {
        // don't work for inner brackets
        if (expression[idx] == '(')
        {
            last_token_idx = expression.find(')');

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
        else if (expression[idx] == '+' || expression[idx] == '*' || expression[idx] == '/' || expression[idx] == '-')
        {
            // add prev operand
            if (last_token_idx != idx)
            {
                if (last_token_idx == 0 && expression[last_token_idx] != '-') // some problems with first token
                {
                    token = std::string_view{expression.data() + last_token_idx, idx - last_token_idx};
                }
                else
                {
                    token = std::string_view{expression.data() + last_token_idx + 1, idx - last_token_idx - 1};
                }
                if (!token.empty()) { tokens.push_back(token); }
            }
            // add operand
            token = std::string_view{expression.data() + idx, 1};
            last_token_idx = idx;
            tokens.push_back(token);
        }
    }

    if (last_token_idx != expression.size() - 1)
    {
        token = std::string_view{expression.data() + last_token_idx + 1, expression.size() - last_token_idx - 1};
        tokens.push_back(token);
    }

    return tokens;
}
