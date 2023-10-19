#pragma once

#include <string_view>
#include <vector>

class Parser 
{
public:
    Parser() {}

    std::vector<std::string_view> operator()(std::string_view) const;

private:
    void сheck_bracket_sequence(std::string_view) const;
    void check_validity(std::string_view) const;
    std::vector<std::string_view> tokenize(std::string_view) const;
    bool isfunc(std::string_view) const noexcept;
    bool isbinaryminus(std::string_view expression, int const idx) const noexcept;
    bool isoperator(const char) const noexcept;
};
