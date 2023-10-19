#include "funcsin.hpp"

#include <cmath>

namespace MyFunc
{

extern "C" double sin(double x) 
{
    return std::sin(x);
}

}
