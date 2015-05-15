#include "print.h"
#include "memory.h"
#include <vector>
using namespace std;


static vector<double> memory;

double getMem(unsigned int index)
{
  //index一番最初の履歴が1
  if(memory.size() < index)
  {
    Println("Out of Index",false);
    Println("num of memory is "+to_string(memory.size()),false);
    return 0;
  }
  return memory[index-1];
}

void pushMemory(double value)
{
	memory.push_back(value);
}