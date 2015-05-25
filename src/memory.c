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
  	return NAN;
  }

  if(i <= 0 || memory.size() < i)
  {
    Println("Out of Index",false);
    Println("num of memory is "+to_String(memory.size()),false);
    return NAN;
  }

  return memory.at(i-1);
}

void pushMemory(double value)
{
	memory.push_back(value);
}

void dispMem(void)
{
  if(memory.empty())
  {
    Println("memory is empty");
    return;
  }
  for(unsigned int i=0;i<memory.size();++i)
  {
     Println("mem("+to_String(i+1)+")="+to_String(memory[i]),false);
  }
}
