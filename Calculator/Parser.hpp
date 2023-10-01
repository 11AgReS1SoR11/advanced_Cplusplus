#include <string>
#include <cmath>
#include <vector>

class Parser 
{
public:
    Parser() {}

    std::vector<std::string_view> operator()(std::string_view) const;

private:
    void сheck_bracket_sequence(std::string_view) const;
    std::vector<std::string_view> tokenize(std::string_view) const;
    bool isfunc(std::string_view) const;
};
