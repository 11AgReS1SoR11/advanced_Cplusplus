#include <string>
#include <cmath>
#include <vector>

class Sorter 
{
public:
    Sorter() {}

    std::vector<std::string_view> operator()(std::vector<std::string_view>) const;

private:
    bool IsAlNum(std::string_view) const;
};