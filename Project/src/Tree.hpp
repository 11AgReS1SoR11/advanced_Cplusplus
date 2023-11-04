#pragma once

#include <vector>
#include <list>
#include <memory>
#include <string>

class Tree;

class Node 
{
public:
    Node(const std::string& _name, const std::string& _data) : name(_name), data(_data) {}

    std::string name;
    std::string data;


    ~Node()
    {
        ObjectList.remove(this);
    }

    bool withoutChildren() const noexcept
    {
        return children.empty();
    }

    // template <typename Functor> 
    // static void for_each(Functor& functor)
    // {
    //     for_each(ObjectList.begin(), ObjectList.end(), functor);
    // }
    std::vector<std::unique_ptr<Node>> children;

private:
    void addChild(std::unique_ptr<Node> child) 
    {
        children.push_back(std::move(child));
    }

    static std::list<Node*> ObjectList;

    friend class Tree;
};

std::list<Node*> Node::ObjectList;

class Tree 
{
public:
    Tree(const std::string& _name, const std::string& _data)
    {
        p_head = std::make_unique<Node>(_name, _data);
    }
    Tree() = default;

    void Add(const std::string& _name, const std::string& _data, std::unique_ptr<Node>& member) 
    {
        if (member == nullptr)
        {
            member = std::make_unique<Node>(_name, _data);
        } 
        else
        {
            auto child = std::make_unique<Node>(_name, _data);
            member->addChild(std::move(child));
        }

        Node* n = new Node(_name, _data);
        Node::ObjectList.push_back(n);
    }

    using Iterator = typename std::list<Node*>::iterator;

    Iterator begin() {
        return Node::ObjectList.begin();
    }

    Iterator end() {
        return Node::ObjectList.end();
    }

    std::unique_ptr<Node> p_head;
// private:
    
};
