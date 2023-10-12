# include <iostream>
# include "Calculator.hpp"

int main()
{
    std::cout << "Welcome" << std::endl;
    std::cout << "Just enter expression and press 'enter'" << std::endl;
    std::cout << "If you wanna leave, just press 'enter' without expression" << std::endl;

    Calculator calc{};
    std::string expression;

    std::cout << "Enter expression: " << std::endl;
    std::getline(std::cin, expression);
    while (expression != "")
    {
        try
        {
            std::cout << "Answer: " << calc(expression) << std::endl;
            std::cout << "Enter expression: " << std::endl;
            std::getline(std::cin, expression);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
    }

    return 0;
}