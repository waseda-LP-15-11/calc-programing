#pragma once
#include <string>
#include <fstream>
#include <vector>

/*
result.txt以外でも
必要な箇所で
Writer writer2("ファイル名")
writer.write("テキスト");
*/
class Writer
{
public:
  Writer(const std::string& path)
  {
    makeNewResultFile(path.c_str());
  }

  Writer(const char* path)
  {
    makeNewResultFile(path);
  }

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

  void writeOneLine();

  void writeCout();
  
  void makeNewResultFile(const char* filename);

private:
  std::ofstream m_ofs;
  std::vector<std::string> m_inputs;
  std::vector<std::string> m_outputs;
};
