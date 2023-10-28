#pragma once

#include <vector>
#include <list>
#include <stack>
#include <string>
#include <memory>

class Tree;

class Node 
{
public:
    Node(const std::string& _name, const std::string& _data, Node* _parent = nullptr) 
        : data{_data}, name{_name}, parent(_parent) {}

    ~Node()
    {
        ObjectList.remove(this);
        // переподвесить детей
    }

    std::string getData() const noexcept
    {
        return data;
    }

    std::string getName() const noexcept
    {
        return name;
    }

    bool withoutChildren() const noexcept
    {
        return children.empty();
    }

    template <typename Functor> 
    static void for_each(Functor& functor)
    {
        for_each(ObjectList.begin(), ObjectList.end(), functor);
    }

private:
    std::string data;
    std::string name;
    Node* parent;
    std::vector<std::unique_ptr<Node>> children;

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
    Tree(const std::string& _data) 
    {
        size_t idx_start = 1, idx_end = _data.find('>');
        std::string name = _data.substr(idx_start, idx_end);
        idx_start = idx_end + 1; idx_end = _data.find('<');
        std::string data = _data.substr(idx_start, idx_end);
        p_head = std::make_unique<Node>(name, data);

        if (_data[idx_end + 1] == '/')
        {
            // детей нет
        }
        else
        {
            // дети есть

        }
    }

    int recurciveAdd(std::string_view str, std::unique_ptr<Node>& cur) // возвращает индекс следующего элемента
    {
        size_t idx_start = 1, idx_end = str.find('>');
        std::string name = str.substr(idx_start, idx_end);
        idx_start = idx_end + 1; idx_end = str.find('<');
        std::string data = str.substr(idx_start, idx_end);
        cur = std::make_unique<Node>(name, data);

        idx_start = str.find(idx_end, '>');

        if (str[idx_end + 1] != '/')
        {
            recurciveAdd
        }

        return str.find(idx_end, '<');
    }

    Tree(const std::string& name, const std::string& data)
    {
        p_head = std::make_unique<Node>(name, data);
    }

    void Add(const std::string& name, const std::string& data) 
    {
        auto child = std::make_unique<Node>(name, data);
        Node::ObjectList.push_back(child.get());
        p_head->addChild(std::move(child));
    }

    using Iterator = typename std::list<Node*>::iterator;

    Iterator begin() 
    {
        return Node::ObjectList.begin();
    }

    Iterator end() 
    {
        return Node::ObjectList.end();
    }

private:
    std::unique_ptr<Node> p_head;
};
