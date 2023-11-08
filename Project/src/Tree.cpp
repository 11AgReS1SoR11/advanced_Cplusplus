
#include "Tree.hpp"

using value_type = Node;
using pointer = Node*;
using reference = Node&;

Tree::Iterator& Tree::Iterator::operator++()
{
    addNextIters();
    if (p_nextNodes.empty()) 
    {
        p_nodePtr = nullptr;
    } 
    else 
    {
        p_nodePtr = p_nextNodes.top();
        p_nextNodes.pop();
    }
    return *this;
}

void Tree::Iterator::addNextIters() 
{
    if (p_nodePtr == nullptr) 
        return;

    for (auto it = p_nodePtr->children.rbegin(); it != p_nodePtr->children.rend(); ++it) 
    {
        p_nextNodes.push(it->get());
    }
}

Tree::Iterator Tree::begin() const noexcept
{
    return Tree::Iterator{p_head.get()};
}

Tree::Iterator Tree::end() const noexcept
{
    return Tree::Iterator{nullptr};
}

Tree::Iterator Tree::Add(const std::string& _name, const std::string& _data, Tree::Iterator member) 
{
    if (p_head == nullptr)
    {
        p_head = std::make_unique<Node>(std::move(_name), std::move(_data));
        return Tree::Iterator{p_head.get()};
    }

    auto child = std::make_unique<Node>(std::move(_name), std::move(_data));
    Tree::Iterator it{child.get()};

    if (member == end())
    {
        p_head->addChild(std::move(child));
    } 
    else
    {
        member->addChild(std::move(child));
    }

    return it;
}

bool Tree::erase(Tree::Iterator member)
{
    if (!p_head) 
        return false;

    if (member == begin()) // delete root case
    {
        if (p_head->withoutChildren())
        {
            p_head.reset();
        }
        else
        {
            auto& tmpChildren = p_head->children;
            auto tmp = std::move(tmpChildren.back());
            for (std::size_t idx = 0; idx < tmpChildren.size() - 1; ++idx)
            {
                tmp->children.push_back(std::move(tmpChildren[idx]));
            }
            p_head.reset();
            p_head = std::move(tmp);
        }
        return true;
    }

    for (auto it = begin(); it != end(); ++it)
    {
        auto childIt = it;
        for (std::size_t cnt = 0; cnt < it->countChildren(); ++cnt)
        {
            if (++childIt == member)
            {
                for (auto& elem : member->children)
                {
                    it->children.push_back(std::move(elem));
                }
                it->children.erase(it->children.begin() + cnt);
                return true;
            }
        }
    }
    return false;
}
