#pragma once

#include <string>
#include "Logger.hpp"
#include "Tree.hpp"
#include "Reader.hpp"

class XMLResuorce
{
public:
    using Iterator = Tree::Iterator;
    using TokenIter = std::vector<std::pair<std::string, std::string>>::iterator;

    static std::unique_ptr<XMLResuorce> create(const std::string& path) 
    {
        auto tokens = Reader::takeData(path);
        return std::unique_ptr<XMLResuorce>(new XMLResuorce{tokens});
    }

    Iterator find(const std::string& name, const std::string& value) const noexcept;

    Iterator add(const std::string& name, const std::string& value, Iterator it);

    bool erase(Iterator eraseIt);

    Iterator begin() const noexcept;

    Iterator end() const noexcept;

private:
    XMLResuorce(std::vector<std::pair<std::string, std::string>>& tokens);

    void recursiveAdd(TokenIter& it, TokenIter& tokenEnd, Iterator cur);

    Tree p_data; // data seems like tree
    Logger& logger;
};