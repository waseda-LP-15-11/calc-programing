#include "sum.h"
#include "args.h"
#include "exmath.h"
#include <numeric>      // std::accumulate
#include <functional>   // std::multiplies
double sum(void)
{
  	const std::vector<double> vec = getArgs();
	return std::accumulate(vec.cbegin(),vec.cend(),0);
}

double ave(void)
{
  return sum() / (getArgs().size());
}

double geometricMean(void)
{
	const std::vector<double> vec = getArgs();
	const double multiOfData = std::accumulate(vec.cbegin(),vec.cend(),1,std::multiplies<double>());
	return pow(multiOfData,1.0/vec.size());
}