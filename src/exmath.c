#include "exmath.h"
double Radians(double degree)
{
	return degree * M_PI / 180.0;
}
double Degrees(double radian)
{
	return radian * 180.0 / M_PI;
}