# include <iostream>
# include "funcsin.hpp"
# include "Calculator.hpp"

int main()
{
    int x = 4, y = 5;
    Calculator calc{};
    std::cout << calc(x, y) << std::endl;
    std::cout << "sin(1) = " << Sin(1.0) << std::endl;
    return 0;
}
