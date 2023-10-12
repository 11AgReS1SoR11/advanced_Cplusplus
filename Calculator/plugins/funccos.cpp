#include "funccos.hpp"

#include <cmath>

namespace MyFunc
{

extern "C" double cos(double x) 
{
    return std::cos(x);
}

}