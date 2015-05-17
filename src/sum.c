#include "sum.h"
#include "args.h"
double sum(void)
{
  	std::vector<double> vec = getArgs();
	double sum = 0;
	for(const auto& v :vec)
		sum += v;
	clearArgs();
	return sum;
}

double ave(void)
{
  int num = getArgs().size();
  double s = sum();
  double average = s / num;
  return average;
}