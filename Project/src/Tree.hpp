#include <vector>
#include <list>
#include <memory>

template <typename T>
class Tree;

template <typename T>
class Node 
{
public:
    Node(const T& value) : data(value) {}

    T data;

    ~Node()
    {
        ObjectList.remove(this);
    }

    bool withoutChildren() const noexcept
    {
        return children->empty();
    }

    template <typename Functor> 
    static void for_each(Functor& functor)
    {
        for_each(ObjectList.begin(), ObjectList.end(), functor);
    }

private:
    std::vector<std::unique_ptr<Node>> children;

    void addChild(std::unique_ptr<Node> child) 
    {
        children.push_back(std::move(child));
    }

    static std::list<Node<T>*> ObjectList;

    friend class Tree<T>;
};

template <typename T>
std::list<Node<T>*> Node<T>::ObjectList;

template <typename T>
class Tree 
{
public:
    Tree(const T& value)
    {
        p_head = std::make_unique<Node<T>>(value);
    }

    void Add(const T& value) 
    {
        auto child = std::make_unique<Node<T>>(value);
        p_head->addChild(std::move(child));
        Node<T>* n = new Node<T>(value);
        Node<T>::ObjectList.push_back(n);
    }

    using Iterator = typename std::list<Node<T>*>::iterator;

    Iterator begin() {
        return Node<T>::ObjectList.begin();
    }

    Iterator end() {
        return Node<T>::ObjectList.end();
    }

private:
    std::unique_ptr<Node<T>> p_head;
};
