#include "args.h"

#include <vector>
static std::vector<double> args;

void pushArg(Expression *arg)
{
	Value v;
	v = eval_expression(arg);
	args.push_back(v.u.num_value);
}
void clearArgs()
{
	args.clear();
}
std::vector<double> getArgs()
{
	return args;
}