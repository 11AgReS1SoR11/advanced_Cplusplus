#include "catch2/catch_all.hpp"

TEST_CASE("nothing")
{
    SECTION("#1")
    {
        REQUIRE_NOTHROW(2 == 2);
    }

    SECTION("#2")
    {
        REQUIRE(2 == 2);
    }
}