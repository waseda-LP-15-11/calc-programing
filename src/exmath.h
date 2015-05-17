#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>

#ifndef M_E
const double M_E        =	2.718281828;
// const double M_LOG2E    =	1.442695041
// const double M_LOG10E   =	0.434294482
// const double M_LN2      =	0.693147181
// const double M_LN10     =	2.302585093
const double M_PI       =	3.141592654;
const double M_PI_2     =	1.570796327;
// const double M_PI_4     =	0.785398163
// const double M_1_PI     =	0.318309886
// const double M_2_PI     =	0.636619772
// const double M_2_SQRTPI =	1.128379167
// const double M_SQRT2    =	1.414213562
// const double M_SQRT1_2  =	0.707106781
#endif

double Radians(double degree);
double Degrees(double radian);
double rightShift(double a,double b);
double leftShift(double a,double b);