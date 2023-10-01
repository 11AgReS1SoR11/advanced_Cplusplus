# include <iostream>
# include "funcsin.hpp"
# include "funccos.hpp"
# include "funcpow.hpp"
# include "Calculator.hpp"

int main()
{
    int x = 4, y = 5;
    std::cout << "sin(1) = " << Sin(1.0) << std::endl;
    std::cout << "cos(1) = " << Cos(1.0) << std::endl;
    std::cout << "4^5 = " << Pow(4, 5) << std::endl;
    return 0;
}
