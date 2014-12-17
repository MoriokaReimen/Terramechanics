#include "bevameter.hpp"
#include <cmath>
using std::pow;
#define _USE_MATH_DEFINES
double bevameter::getShear(const double& M, const double& r_i = 5.0, const double& r_o = 10.0)
{
    double shear = 1.50 / (pow(r_o, 3) - pow(r_i, 3)) / M_PI;
    return shear;
}

