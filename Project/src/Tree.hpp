#pragma once

#include <vector>
#include <memory>
#include <string>
#include <stack>

class Tree;

class Node 
{
public:
    Node(const std::string& _name, const std::string& _data) : name(_name), data(_data) {}

    std::string getName() const noexcept
    {
        return name;
    }

    std::string getData() const noexcept
    {
        return data;
    }

    bool withoutChildren() const noexcept
    {
        return children.empty();
    }

private:
    std::string name;
    std::string data;
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

private:
    std::unique_ptr<Node> p_head;

    class Iterator
    {
    public:
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        Iterator(Node* ptr) : ptr_(ptr) { initializeNextNode(); }

        Iterator& operator++() 
        {
            if (nodeStack.empty()) 
            {
                ptr_ = nullptr;
            } 
            else 
            {
                ptr_ = nodeStack.top();
                nodeStack.pop();
                initializeNextNode();
            }
            return *this;
        }

        reference operator*()
        {
            return *ptr_;
        }

        pointer operator->()
        {
            return ptr_;
        }

        // value_type operator*() const
        // {
        //     return *ptr_;
        // }

        const pointer operator->() const
        {
            return ptr_;
        }

        bool operator==(const Iterator& other) const
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const
        {
            return ptr_ != other.ptr_;
        }

    private:
        Node* ptr_;

        std::stack<Node*> nodeStack;
        void initializeNextNode() 
        {
            if (ptr_ == nullptr) return;
            for (auto it = ptr_->children.rbegin(); it != ptr_->children.rend(); ++it) 
            {
                nodeStack.push(it->get());
            }
        }
    };

public:
    Iterator begin() 
    {
        return Iterator{p_head.get()};
    }

    Iterator end() 
    {
        return Iterator{nullptr};
    }

    void Add(const std::string& _name, const std::string& _data, Iterator member = Iterator{nullptr}) 
    {
        if (member == end())
        {
            if (p_head == nullptr)
            {
                p_head = std::make_unique<Node>(_name, _data);
            }
            else
            {
                auto child = std::make_unique<Node>(_name, _data);
                p_head->addChild(std::move(child));
            }
        } 
        else
        {
            auto child = std::make_unique<Node>(_name, _data);
            member->addChild(std::move(child));
        }
    }
};
