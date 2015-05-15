#pragma once
#include <string>
#include <fstream>
#include <iostream>
class Writer
{
public:
  Writer(const std::string& path):
	m_ofs(path)
  {}

  ~Writer()
  {
    m_ofs.close();
  }

  template<typename Type>
  void write(const Type& value)
  {
    	m_ofs << value;
  }

  template<typename Type>
  void writeln(const Type& value)
  {
  	write(value);
	nextLine();
  }

  void nextLine()
  {
    m_ofs << "\n";
  }

private:
  std::ofstream m_ofs;
};
