#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Tree.hpp"
#include "Reader.hpp"

class XMLResuorce
{
public:
    using Iterator = Tree::Iterator;

    static std::unique_ptr<XMLResuorce> create(const std::string& path) 
    {
        auto tokens = Reader::takeData(path);
        return std::unique_ptr<XMLResuorce>(new XMLResuorce{tokens});
    }

    Iterator begin()
    {
        return data.begin();
    }

    Iterator end()
    {
        return data.end();
    }

private:
    XMLResuorce(std::vector<std::pair<std::string, std::string>>& tokens)
    {
        auto tokenBegin = tokens.begin();
        auto dataBegin = data.begin();
        data.Add(std::move(tokenBegin->first), std::move(tokenBegin->second), data.begin());
        dataBegin = data.begin();
        ++tokenBegin;
        recursiveAdd(tokenBegin, dataBegin);
    }

    void recursiveAdd(std::vector<std::pair<std::string, std::string>>::iterator& it, Iterator cur)
    {
        while (it->first != "")
        {
            data.Add(std::move(it->first), std::move(it->second), cur);
            Iterator newCur{cur};
            recursiveAdd(++it, ++newCur);
        }
        ++it;
    }

private:
    Tree data; // data seems like tree
};