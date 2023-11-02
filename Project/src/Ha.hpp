#pragma once
#include <vector>
#include <memory>
#include <functional>

template <class T>
struct point
{
    point (T _x, T _y) : x(_x), y(_y) {}
    T x;
    T y;
};

template <class T>
class pointArr
{
public:
    static std::unique_ptr<pointArr<T>> create(std::vector<point<T>> arr_other)
    {
        auto* ptr = new pointArr<T>(arr_other);
        return std::unique_ptr<pointArr<T>>(ptr);
    }

    std::unique_ptr<pointArr<T>> clone()
    {
        auto* ptr = new pointArr<T>(*this);
        return std::unique_ptr<pointArr<T>>(ptr);
    }

    void multi_push(std::vector<point<T>> arr_other)
    {
        for (auto const& i : arr_other)
        {
            arr.push_back(i);
        }
    }

    void push(const point<T>& p)
    {
        arr.push_back(p);
    }

    void pop()
    {
        arr.pop_back();
    }

    point<T>& operator [](int idx)
    {
        return arr[idx];
    }

    point<T> operator [](int idx) const
    {
        return arr[idx];
    }


    T process(std::function<T(std::vector<point<T>>&)> f)
    {
        return f(arr);
    }



private:
    pointArr() = default;
    pointArr(std::vector<point<T>> arr_other) { for (auto i : arr_other) arr.push_back(i); }
    pointArr(const pointArr& another) = default;

    std::vector<point<T>> arr;
};