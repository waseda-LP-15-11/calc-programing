#include "exmath.h"
double Radians(double degree)
{
	return degree * M_PI / 180.0;
}
double Degrees(double radian)
{
	return radian * 180.0 / M_PI;
}
double rightShift(double a,double b)
{
	return static_cast<unsigned int>(a) >> static_cast<unsigned int>(b);
}
double leftShift(double a,double b)
{
	return static_cast<unsigned int>(a) << static_cast<unsigned int>(b);
}