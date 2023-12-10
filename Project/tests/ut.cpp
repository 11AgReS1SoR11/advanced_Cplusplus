#include "catch2/catch_all.hpp"
#include <iostream>
#include "../src/Wrapper.hpp"
#include "../src/Engine.hpp"

struct A
{
    int sum(int a, int b) { return a + b; }
    int incr(int a) { return a + 1; }
};

struct B
{
    int mult(int a, int b) { return a * b; }
};

TEST_CASE("Testing Wrapper")
{
    A calc;
    B calc2;

    SECTION("successful outcome")
    {
        SECTION("#1")
        {
            Wrapper<A, int, int> wrapper(&calc, &A::sum, {{"arg1", 0}, {"arg2", 0}});
            REQUIRE(wrapper.Invoke({{"arg1", 1}, {"arg2", 2}}) == 3);
        }
        SECTION("#2")
        {
            Wrapper<A, int> wrapper(&calc, &A::incr, {{"arg1", 0}});
            REQUIRE(wrapper.Invoke({{"arg1", 7}}) == 8);
        }
        SECTION("#3")
        {
            Wrapper<B, int, int> wrapper(&calc2, &B::mult, {{"arg1", 0}, {"arg2", 0}});
            REQUIRE(wrapper.Invoke({{"arg1", 7}, {"arg2", 5}}) == 35);
        }
    }

    SECTION("failure outcome")
    {
        SECTION("#1 incorrect amount of arguments")
        {
            Wrapper<A, int, int> wrapper(&calc, &A::sum, {{"arg1", 0}, {"arg2", 0}});
            REQUIRE_THROWS_WITH(wrapper.Invoke({{"arg1", 1}}), "No such argument: arg2");
        }
        SECTION("#2 incorrect name of arguments")
        {
            Wrapper<A, int, int> wrapper(&calc, &A::sum, {{"arg1", 0}, {"arg2", 0}});
            REQUIRE_THROWS_WITH(wrapper.Invoke({{"arg1", 1}, {"lalalal", 2}}), "No such argument: arg2");
        }
    }
}

TEST_CASE("Testing Engine")
{
    A calc;
    B calc2;

    Engine engine;

    Wrapper<A, int, int> wrapper1(&calc, &A::sum, {{"arg1", 0}, {"arg2", 0}});
    Wrapper<A, int> wrapper2(&calc, &A::incr, {{"arg1", 0}});
    Wrapper<B, int, int> wrapper3(&calc2, &B::mult, {{"arg1", 0}, {"arg2", 0}});

    engine.register_command("command1", &wrapper1);
    engine.register_command("command2", &wrapper2);
    engine.register_command("command3", &wrapper3);

    SECTION("successful outcome")
    {
        REQUIRE(engine.execute("command1", {{"arg1", 1}, {"arg2", 2}}) == 3);
        REQUIRE(engine.execute("command2", {{"arg1", 7}}) == 8);
        REQUIRE(engine.execute("command3", {{"arg1", 7}, {"arg2", 5}}) == 35);
    }

    SECTION("failure outcome")
    {
        SECTION("#1 incorrect amount of arguments")
        {
            REQUIRE_THROWS_WITH(engine.execute("command1", {{"arg1", 1}}), "No such argument: arg2");
        }
        SECTION("#2 incorrect name of arguments")
        {
            REQUIRE_THROWS_WITH(engine.execute("command1", {{"arg1", 1}, {"lalalala", 3}}), "No such argument: arg2");
        }
        SECTION("#3 incorrect name of command")
        {
            REQUIRE_THROWS_WITH(engine.execute("lalalala", {{"arg1", 1}, {"lalalala", 3}}), "No such command: lalalala");
        }
    }
}

