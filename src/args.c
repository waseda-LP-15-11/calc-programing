#include "args.h"
#include <vector>
static std::vector<double> args;

void pushArg(double arg)
{
	args.push_back(arg);
}
void clearArgs()
{
	args.clear();
}
std::vector<double> getArgs()
{
	return args;
}