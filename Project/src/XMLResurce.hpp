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
        auto tokens = Reader::takeData(path);
        return std::unique_ptr<XMLResuorce>(new XMLResuorce{tokens});
    }

private:
    XMLResuorce(std::vector<std::pair<std::string, std::string>>& tokens)
    {
        for (auto& token : tokens)
        {
            std::cout << "name: [" << token.first << "] value: [" << token.second << "]" << std::endl;
            if (token.first.empty())
            {
                //data.Add(std::move(token.first), std::move(token.second));
            }
            else
            {
                data.Add(std::move(token.first), std::move(token.second));
            }
            
        }
    }


public:
    Tree data; // данные в виде дерева
};