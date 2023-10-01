#include "catch2/catch_all.hpp"

#include "funcsin.hpp"
#include "funccos.hpp"
#include "funcpow.hpp"
#include <cmath>

TEST_CASE("testing the correctness of functions") 
{
    dobule eps = 0.00001;
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
