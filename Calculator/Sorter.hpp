#include <string_view>
#include <vector>
#include <unordered_map>

class Sorter 
{
public:
    Sorter() {}

    std::vector<std::string_view> operator()(const std::vector<std::string_view>) const;

    bool IsAlNum(std::string_view) const noexcept;

private:
    const std::unordered_map<std::string_view, size_t> priorities = {
        {")", 0},
        {"(", 0},
        {"+", 2},
        {"-", 2},
        {"*", 3},
        {"/", 3},
        {"^", 4},
        {"sin", 4},
        {"cos", 4}
    };
};