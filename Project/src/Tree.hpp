#pragma once

#include <vector>
#include <memory>
#include <string>
#include <stack>

class Tree;

class Node 
{
public:
    Node(const std::string& _name, const std::string& _data) : p_name(_name), p_data(_data) {}

    std::string getName() const noexcept
    {
        return p_name;
    }

    std::string getData() const noexcept
    {
        return p_data;
    }

    bool withoutChildren() const noexcept
    {
        return children.empty();
    }

    std::size_t countChildren() const noexcept
    {
        return children.size();
    }

private:
    std::string p_name;
    std::string p_data;
    std::vector<std::unique_ptr<Node>> children;

    void addChild(std::unique_ptr<Node> child) 
    {
        children.push_back(std::move(child));
    }

    friend class Tree;
};

class Tree
{
public:
    Tree(const std::string& _name, const std::string& _data)
    {
        p_head = std::make_unique<Node>(_name, _data);
    }

    Tree() = default;

    class Iterator
    {
    public:
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        Iterator(Node* ptr) : p_nodePtr(ptr) {}

        Iterator& operator++();

        reference operator*() noexcept
        {
            return *p_nodePtr;
        }

        pointer operator->() noexcept
        {
            return p_nodePtr;
        }

        const pointer operator->() const noexcept
        {
            return p_nodePtr;
        }

        bool operator==(const Iterator& other) const noexcept
        {
            return p_nodePtr == other.p_nodePtr;
        }

        bool operator!=(const Iterator& other) const noexcept
        {
            return p_nodePtr != other.p_nodePtr;
        }

    private:
        Node* p_nodePtr;

        std::stack<Node*> p_nextNodes;
        void addNextIters();
    };

    Iterator begin() const noexcept;

    Iterator end() const noexcept;

    Iterator Add(const std::string& _name, const std::string& _data, Iterator member = Iterator{nullptr});

    bool erase(Iterator member);

private:
    std::unique_ptr<Node> p_head;
};
