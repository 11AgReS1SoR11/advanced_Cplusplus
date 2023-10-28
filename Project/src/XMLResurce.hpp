#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Tree.hpp"
#include "Reader.hpp"

class XMLResuorce
{
public:
    static std::unique_ptr<XMLResuorce> create(const std::string& path) 
    {
        std::string dateText = Reader::takeData(path);
        return std::make_unique<XMLResuorce>(dateText);
    }

private:
    XMLResuorce(const std::string& _data) : data{_data} {}


private:
    Tree data; // данные в виде дерева
};