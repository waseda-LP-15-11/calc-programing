#include "print.h"
#include "memory.h"
#include "exmath.h"
#include <vector>
using namespace std;


static vector<double> memory;

double getMem(double index)
{
  //index一番最初の履歴が1
  const unsigned int i = static_cast<size_t>(index);

  if(std::isnan(index))
  {
	Println("Index is Not a Number",false);
	return 0;
  }

  if(i <= 0 || memory.size() < i)
  {
	Println("Out of Index",false);
    	Println("num of memory is "+to_string(memory.size()),false);
    	return 0;
  }

  return memory.at(i-1);
}

void pushMemory(double value)
{
	memory.push_back(value);
}