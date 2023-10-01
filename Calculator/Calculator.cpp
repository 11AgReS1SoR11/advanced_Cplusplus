#include "Calculator.hpp"

double Calculator::operator()(std::string_view expression) const
{
    auto tokenz = parser(expression);
    return 0;
}
