#include "funccos.hpp"

#include <cmath>

extern "C" double Cos(double x) 
{
    return std::cos(x);
}
