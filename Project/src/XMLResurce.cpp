
#include "XMLResurce.hpp"

using Iterator = Tree::Iterator;
using TokenIter = std::vector<std::pair<std::string, std::string>>::iterator;

Iterator XMLResuorce::find(const std::string& name, const std::string& value) const noexcept
{
    logger << "finding [" << name << value << "]";

    for (auto it = p_data.begin(); it != p_data.end(); ++it)
    {
        if (it->getName() == name && it->getData() == value)
        {
            logger << "found [" << name << value << "]";
            return it;
        }
    }

    logger << "didn't find [" << name  << value << "]";
    return p_data.end();
}

Iterator XMLResuorce::add(const std::string& name, const std::string& value, Iterator it)
{
    if (it != end()) logger << "Add: [" << name << value << "] to [" << it->getName() << it->getData() << "]";
    else logger << "Add: [" << name << value << "] to HEAD";

    return p_data.Add(name, value, it);
}

bool XMLResuorce::erase(Iterator eraseIt)
{
    logger << "Deleting: [" << eraseIt->getName() << eraseIt->getData() << "]";

    bool success = p_data.erase(eraseIt);
    if (success) logger << "Deleted seccussful";
    else logger << "Deleted unseccussful";

    return success;
}

Iterator XMLResuorce::begin() const noexcept
{
    return p_data.begin();
}

Iterator XMLResuorce::end() const noexcept
{
    return p_data.end();
}

XMLResuorce::XMLResuorce(std::vector<std::pair<std::string, std::string>>& tokens) : logger{Logger::getInstance()}
{
    logger << "Creating XMLResuorce";

    auto tokenBegin = tokens.begin();
    auto tokenEnd = tokens.end();
    auto dataBegin = p_data.begin();
    recursiveAdd(tokenBegin, tokenEnd, dataBegin);

    logger << "Created successful";
}

void XMLResuorce::recursiveAdd(TokenIter& it, TokenIter& tokenEnd, Iterator cur)
{
    while (it != tokenEnd && !it->first.empty())
    {
        if (cur != end()) logger << "Adding: [" << it->first << it->second << "] to [" << cur->getName() << cur->getData() << "]";
        else logger << "Adding: [" << it->first << it->second << "] to HEAD";

        auto childIt = p_data.Add(std::move(it->first), std::move(it->second), cur);
        recursiveAdd(++it, tokenEnd, childIt);
    }
    ++it;
}
