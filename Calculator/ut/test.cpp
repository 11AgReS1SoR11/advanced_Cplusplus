#include "catch2/catch_all.hpp"

#include "../plugins/funcsin.hpp"
#include "../plugins/funccos.hpp"
#include "../plugins/funcpow.hpp"
#include "../Calculator.hpp"
#include <cmath>

TEST_CASE("testing the correctness of functions") 
{
    double const eps = 0.00001;
    REQUIRE(fabs(MyFunc::Sin(1) - std::sin(1)) < eps);
    REQUIRE(fabs(MyFunc::Sin(0) - std::sin(0)) < eps);
    REQUIRE(fabs(MyFunc::Sin(-1) - std::sin(-1)) < eps);

    REQUIRE(fabs(MyFunc::Cos(1) - std::cos(1)) < eps);
    REQUIRE(fabs(MyFunc::Cos(0) - std::cos(0)) < eps);
    REQUIRE(fabs(MyFunc::Cos(-1) - std::cos(-1)) < eps);

    REQUIRE(fabs(MyFunc::Pow(1, 3) - std::pow(1, 3)) < eps);
    REQUIRE(fabs(MyFunc::Pow(0, 4) - std::pow(0, 4)) < eps);

    REQUIRE_THROWS_WITH(MyFunc::Pow(-1, 3), "Exponential expression less than 0");
    REQUIRE_THROWS_WITH(MyFunc::Pow(-1, 2), "Exponential expression less than 0");
}

TEST_CASE("testing parser")
{
    SECTION("simple expression #1 (plus)")
    {
        std::string expression = "3+2";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "3");
        REQUIRE(tokens[1] == "+");
        REQUIRE(tokens[2] == "2");
    }

    SECTION("simple expression #2 (mult)")
    {
        std::string expression = "3*2";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "3");
        REQUIRE(tokens[1] == "*");
        REQUIRE(tokens[2] == "2");
    }

    SECTION("simple expression #3 (dev)")
    {
        std::string expression = "3/2";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "3");
        REQUIRE(tokens[1] == "/");
        REQUIRE(tokens[2] == "2");
    }

    SECTION("simple expression #4 (negative)")
    {
        std::string expression = "-3";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "-3");
    }

    SECTION("simple expression #5 (brackets)")
    {
        std::string expression = "(3+2)";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "(");
        REQUIRE(tokens[1] == "3");
        REQUIRE(tokens[2] == "+");
        REQUIRE(tokens[3] == "2");
        REQUIRE(tokens[4] == ")");
    }

    SECTION("simple expression #6 (sin)")
    {
        std::string expression = "sin(3)";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "sin");
        REQUIRE(tokens[1] == "(");
        REQUIRE(tokens[2] == "3");
        REQUIRE(tokens[3] == ")");
    }

    SECTION("simple expression #7 (cos)")
    {
        std::string expression = "cos(3)";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "cos");
        REQUIRE(tokens[1] == "(");
        REQUIRE(tokens[2] == "3");
        REQUIRE(tokens[3] == ")");
    }

    SECTION("simple expression #8 (^)")
    {
        std::string expression = "3^5";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "3");
        REQUIRE(tokens[1] == "^");
        REQUIRE(tokens[2] == "5");
    }

    SECTION("complex expression #1")
    {
        std::string expression = "3+2/2.5*14";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "3");
        REQUIRE(tokens[1] == "+");
        REQUIRE(tokens[2] == "2");
        REQUIRE(tokens[3] == "/");
        REQUIRE(tokens[4] == "2.5");
        REQUIRE(tokens[5] == "*");
        REQUIRE(tokens[6] == "14");
    }

    SECTION("complex expression #2")
    {
        std::string expression = "-3/(2-2.5)*0.1";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "-3");
        REQUIRE(tokens[1] == "/");
        REQUIRE(tokens[2] == "(");
        REQUIRE(tokens[3] == "2");
        REQUIRE(tokens[4] == "-");
        REQUIRE(tokens[5] == "2.5");
        REQUIRE(tokens[6] == ")");
        REQUIRE(tokens[7] == "*");
        REQUIRE(tokens[8] == "0.1");
    }

    SECTION("complex expression #3")
    {
        std::string expression = "cos(5*2)^sin(3)";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_NOTHROW(tokens = parser(expression));
        REQUIRE(tokens[0] == "cos");
        REQUIRE(tokens[1] == "(");
        REQUIRE(tokens[2] == "5");
        REQUIRE(tokens[3] == "*");
        REQUIRE(tokens[4] == "2");
        REQUIRE(tokens[5] == ")");
        REQUIRE(tokens[6] == "^");
        REQUIRE(tokens[7] == "sin");
        REQUIRE(tokens[8] == "(");
        REQUIRE(tokens[9] == "3");
        REQUIRE(tokens[10] == ")");
    }

    SECTION("failure outcome")
    {
        std::string expression = "(3+2)(";
        Parser parser{};
        std::vector<std::string_view> tokens{};
        REQUIRE_THROWS_WITH(tokens = parser(expression), "Wrong expression (check brackets)");
    }
}

TEST_CASE("testing sorter")
{
    SECTION("simple expression #1")
    {
        std::vector<std::string_view> tokens{"2", "+", "3", "*", "1"};
        Sorter sorter{};
        std::vector<std::string_view> sorted_tokens{};
        REQUIRE_NOTHROW(sorted_tokens = sorter(tokens));
        REQUIRE(sorted_tokens[0] == "2");
        REQUIRE(sorted_tokens[1] == "3");
        REQUIRE(sorted_tokens[2] == "1");
        REQUIRE(sorted_tokens[3] == "*");
        REQUIRE(sorted_tokens[4] == "+");
    }

    SECTION("simple expression #2")
    {
        std::vector<std::string_view> tokens{"(", "2", "+", "3", ")", "*", "1"};
        Sorter sorter{};
        std::vector<std::string_view> sorted_tokens{};
        REQUIRE_NOTHROW(sorted_tokens = sorter(tokens));
        REQUIRE(sorted_tokens[0] == "2");
        REQUIRE(sorted_tokens[1] == "3");
        REQUIRE(sorted_tokens[2] == "+");
        REQUIRE(sorted_tokens[3] == "1");
        REQUIRE(sorted_tokens[4] == "*");
    }

    SECTION("complex expression #1")
    {
        std::vector<std::string_view> tokens{"sin", "(", "2", ")", "*", "(", "-2", "+", "13", ")"};
        Sorter sorter{};
        std::vector<std::string_view> sorted_tokens{};
        REQUIRE_NOTHROW(sorted_tokens = sorter(tokens));
        REQUIRE(sorted_tokens[0] == "2");
        REQUIRE(sorted_tokens[1] == "sin");
        REQUIRE(sorted_tokens[2] == "-2");
        REQUIRE(sorted_tokens[3] == "13");
        REQUIRE(sorted_tokens[4] == "+");
        REQUIRE(sorted_tokens[5] == "*");
    }

    SECTION("complex expression #2")
    {
        std::vector<std::string_view> tokens{"4", "+", "2", "^", "(", "-5", "*", "sin", "(", "12", ")", ")"};
        Sorter sorter{};
        std::vector<std::string_view> sorted_tokens{};
        REQUIRE_NOTHROW(sorted_tokens = sorter(tokens));
        REQUIRE(sorted_tokens[0] == "4");
        REQUIRE(sorted_tokens[1] == "2");
        REQUIRE(sorted_tokens[2] == "-5");
        REQUIRE(sorted_tokens[3] == "12");
        REQUIRE(sorted_tokens[4] == "sin");
        REQUIRE(sorted_tokens[5] == "*");
        REQUIRE(sorted_tokens[6] == "^");
    }
}

TEST_CASE("testing loader")
{
    SECTION("load sin and cos")
    {
        Loader loader{};
        REQUIRE_NOTHROW(loader.loadFunction<double(double)>("plugins/libfuncsin.so", "Sin"));
        auto Sin = loader.loadFunction<double(double)>("plugins/libfuncsin.so", "Sin");
        REQUIRE(Sin(0) == 0);
        REQUIRE_NOTHROW(loader.loadFunction<double(double)>("plugins/libfunccos.so", "Cos"));
        auto Cos = loader.loadFunction<double(double)>("plugins/libfunccos.so", "Cos");
        REQUIRE(Cos(0) == 1);
    }

    SECTION("load ^ (two arguments)")
    {
        Loader loader{};
        REQUIRE_NOTHROW(loader.loadFunction<double(double, double)>("plugins/libfuncpow.so", "Pow"));
        auto Pow = loader.loadFunction<double(double, double)>("plugins/libfuncpow.so", "Pow");
        REQUIRE(Pow(2,2) == 4);
    }

    SECTION("failure outcome")
    {
        Loader loader{};
        REQUIRE_THROWS_WITH(loader.loadFunction<double(double, double)>("PLUGIN/libfuncpow.so", "Pow"), 
        "Error loading library: PLUGIN/libfuncpow.so: cannot open shared object file: No such file or directory");

        // don't cross platform, but working
        // REQUIRE_THROWS_WITH(loader.loadFunction<double(double, double)>("plugins/libfuncpow.so", "tangens"), 
        // "Error loading symbol: /home/daniil/Рабочий стол/advanced_c/advanced_Cplusplus-1/build/plugins/libfuncpow.so: undefined symbol: tangens");
    }
}

TEST_CASE("testing calculator")
{
    SECTION("simple expression #1")
    {
        std::string expression = "2+2";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(answer == 4);
    }

    SECTION("simple expression #2")
    {
        std::string expression = "-2.5+2.5*2";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(answer == 2.5);
    }

    SECTION("simple expression #3")
    {
        std::string expression = "sin(0)";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(answer == 0);
    }

    SECTION("simple expression #3")
    {
        std::string expression = "3*(3-1)";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(answer == 6);
    }

    SECTION("complex expression #1")
    {
        std::string expression = "sin(0)-12^(3-1)";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(answer == -144);
    }

    SECTION("complex expression #2")
    {
        std::string expression = "cos(3.14)*15^(4/2-sin(0+0))";
        Calculator calc{};
        double answer;
        REQUIRE_NOTHROW(answer = calc(expression));
        REQUIRE(fabs(answer - -224.9997146387) < 0.000001);
    }

    SECTION("failure outcome")
    {
        SECTION("Incorrect enter #1")
        {
            std::string expression = "2+3-(1";
            Calculator calc{};
            double answer;
            REQUIRE_THROWS_WITH(answer = calc(expression), "Wrong expression (check brackets)");
        }

        SECTION("Incorrect enter #2")
        {
            std::string expression = "2+3-Yaml";
            Calculator calc{};
            double answer;
            REQUIRE_THROWS_WITH(answer = calc(expression), "Incorrect enter");
        }

        SECTION("Incorrect enter #3")
        {
            std::string expression = "1+tg(2)";
            Calculator calc{};
            double answer;
            REQUIRE_THROWS_WITH(answer = calc(expression), "Incorrect enter");
        }

        SECTION("Division by zero")
        {
            std::string expression = "10/0";
            Calculator calc{};
            double answer;
            REQUIRE_THROWS_WITH(answer = calc(expression), "division by 0");
        }
    }
}