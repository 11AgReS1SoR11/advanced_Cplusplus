#include "funcsin.hpp"

#include <cmath>

extern "C" double Sin(double x) 
{
    return std::sin(x);
}
