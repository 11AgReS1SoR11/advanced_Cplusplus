#include "catch2/catch_all.hpp"
#include <iostream>

#include "../funcsin.hpp"
#include "../funccos.hpp"
#include "../funcpow.hpp"
#include "../Parser.hpp"

TEST_CASE("testing the correctness of functions") 
{
    double eps = 0.00001;
    REQUIRE(fabs(Sin(1) - std::sin(1)) < eps);
    REQUIRE(fabs(Sin(0) - std::sin(0)) < eps);
    REQUIRE(fabs(Sin(-1) - std::sin(-1)) < eps);

    REQUIRE(fabs(Cos(1) - std::cos(1)) < eps);
    REQUIRE(fabs(Cos(0) - std::cos(0)) < eps);
    REQUIRE(fabs(Cos(-1) - std::cos(-1)) < eps);

    REQUIRE(fabs(Pow(1, 3) - std::pow(1, 3)) < eps);
    REQUIRE(fabs(Pow(0, 4) - std::pow(0, 4)) < eps);

    REQUIRE_THROWS_WITH(Pow(-1, 3), "Exponential expression less than 0");
    REQUIRE_THROWS_WITH(Pow(-1, 2), "Exponential expression less than 0");
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
        REQUIRE(tokens[0] == "-");
        REQUIRE(tokens[1] == "3");
    }

    SECTION("simple expression #4 (brackets)")
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
        REQUIRE(tokens[0] == "-");
        REQUIRE(tokens[1] == "3");
        REQUIRE(tokens[2] == "/");
        REQUIRE(tokens[3] == "(");
        REQUIRE(tokens[4] == "2");
        REQUIRE(tokens[5] == "-");
        REQUIRE(tokens[6] == "2.5");
        REQUIRE(tokens[7] == ")");
        REQUIRE(tokens[8] == "*");
        REQUIRE(tokens[9] == "0.1");
    }

}
