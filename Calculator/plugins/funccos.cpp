#include "funccos.hpp"

#include <cmath>

namespace MyFunc
{

extern "C" double Cos(double x) 
{
    return std::cos(x);
}

}