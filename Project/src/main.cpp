#include <iostream>
#include <algorithm>
#include <cmath>
#include "Ha.hpp"

int main() 
{

    auto f = [](std::vector<point<int>> points)
    {
        double max1 = -1;
        for (size_t i = 0; i < points.size()-1; ++i)
        {
            for (size_t j = i+1; j < points.size(); ++j)
            {
                max1 = std::max(max1, std::sqrt(std::pow(points[i].x - points[j].x, 2) + std::pow(points[i].y - points[j].y, 2)));
            }
        }
        return max1;
    };

    point<int> p1{1, 2}, p2{2, 2}, p3{3, 1};

    std::vector<point<int>> vec = {p1, p2, p3};

    auto pointArr1 = pointArr<int>::create(vec);

    auto pointArr2 = pointArr1->clone();

    std::cout << pointArr1->process(f) << std::endl;
    std::cout << pointArr2->process(f) << std::endl;

    point<int> p4{90, 20};
    pointArr1->push(p4);
    std::cout << pointArr1->process(f) << std::endl;

    return 0;
}
