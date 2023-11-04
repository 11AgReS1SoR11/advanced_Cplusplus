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
        for (auto elem : x)
        {
            std::cout << "name: [" << elem.first << "] value: [" << elem.second << "]" << std::endl;
        }
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
        Tree x{"name", "data"};

        x.Add("name2", "data2", x.p_head);

        x.Add("name3", "data3", x.p_head->children.back());
        x.Add("name33", "data33", x.p_head->children.back());

        std::cout << x.p_head->name << " - " << x.p_head->data << std::endl;

        for (auto& mem : x.p_head->children)
        {
            std::cout << mem->name << " - " << mem->data << std::endl;
            for (auto& mem2 : mem->children)
            {
                std::cout << mem2->name << " - " << mem2->data << std::endl;
            }
        }


    }

    // SECTION("failure outcome")
    // {
    //     REQUIRE_THROWS_WITH(Reader::takeData("LALALALALA"), "Failed to open the XML file");
    // }
}


TEST_CASE("Testing XMLResurces")
{
    SECTION("successful outcome")
    {
        auto x = XMLResuorce::create("../resources/res.xml");

        for (auto y = x->data.begin(); y != x->data.end(); y++)
        {
            std::cout << (*y)->data << std::endl;
        }
    }
}
