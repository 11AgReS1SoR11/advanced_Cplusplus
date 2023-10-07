#include "funcsin.hpp"

#include <cmath>

namespace MyFunc
{

extern "C" double Sin(double x) 
{
    return std::sin(x);
}

}
