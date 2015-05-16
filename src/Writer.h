#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
/*
result.txt以外でも
必要な箇所で
Writer writer2("ファイル名")
writer.write("テキスト");
*/
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

  void writeInput(const std::string& value)
  {
    m_inputs.push_back(value);
  }

  void writeOutput(const std::string& value)
  {
    m_outputs.push_back(value);
  }
  
  void writeOneLine()
  {	
  	m_ofs << ">> ";
  	for(size_t i=0;i<m_inputs.size();++i)
  	{
  		 m_ofs << m_inputs[i];
  	}
  	m_ofs << std::endl;
  	for(size_t i=0;i<m_outputs.size();++i)
  	{
  		 m_ofs << m_outputs[i] << std::endl;
  	}
  	m_inputs.clear();
  	m_outputs.clear();
  }
  
  void writeCout()
  {
    	std::cout << ">> ";
  	for(size_t i=0;i<m_inputs.size();++i)
  	{
  		 std::cout << m_inputs[i];
  	}
  	std::cout << std::endl;
  	for(size_t i=0;i<m_outputs.size();++i)
  	{
  		 std::cout << m_outputs[i] << std::endl;
  	}
  }

private:
  std::ofstream m_ofs;
  std::vector<std::string> m_inputs;
  std::vector<std::string> m_outputs;
};
