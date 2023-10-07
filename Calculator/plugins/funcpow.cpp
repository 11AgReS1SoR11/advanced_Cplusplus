#include "funcpow.hpp"

#include <stdexcept>
#include <cmath>

namespace MyFunc
{

extern "C" double Pow(double x, double y) 
{
    if (x < 0) throw std::runtime_error("Exponential expression less than 0");
    return std::pow(x, y);
}

}