#include "catch2/catch_all.hpp"
#include <iostream>

#include "Reader.hpp"
#include "Tree.hpp"
#include "XMLResurce.hpp"

TEST_CASE("Testing Reader")
{
    SECTION("successful outcome")
    {
        auto x = Reader::takeData("../resources/res.xml");
        REQUIRE(!x.empty());
    }

    SECTION("failure outcome")
    {
        REQUIRE_THROWS_WITH(Reader::takeData("LALALALALA"), "Failed to open the XML file");
    }
}


TEST_CASE("Testing Tree")
{
    SECTION("successful outcome")
    {
        Tree x{"name1", "data1"};

        REQUIRE_NOTHROW(x.Add("name2", "data2"));
        REQUIRE_NOTHROW(x.Add("name1_child", "data1_child", x.begin()));

        auto it = x.begin();

        REQUIRE(it->getName() == "name1");
        REQUIRE(it->getData() == "data1");

        ++it;

        REQUIRE(it->getName() == "name2");
        REQUIRE(it->getData() == "data2");

        ++it;

        REQUIRE(it->getName() == "name1_child");
        REQUIRE(it->getData() == "data1_child");

        ++it;

        REQUIRE(it == x.end());
    }
}


TEST_CASE("Testing XMLResurces")
{
    SECTION("successful outcome")
    {
        auto x = XMLResuorce::create("../resources/res.xml");
    }
}
