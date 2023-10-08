# include <iostream>
# include "Calculator.hpp"

int main()
{
    // Demo of calculator is present here
    Calculator calc{};
    std::string expression = "2+2";
    std::cout << calc(expression) << std::endl;
    expression = "sin(4*2)/19";
    std::cout << calc(expression) << std::endl;
    expression = "sin(28900.195)/19.5^(1/cos(3-27.5*3))";
    std::cout << calc(expression) << std::endl;

    try
    {
        expression = "1/0";
        double result = calc(expression);
        std::cout << result << std::endl;
    } catch (const std::runtime_error& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
