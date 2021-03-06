﻿#pragma once
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
  Writer(const std::string& path,bool fileCheck=true):
	m_ofs(makeNewFileName(path,fileCheck))
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
  
  //m_inputsとm_outputsを書き出す
  void writeOneLine();
  
  //ファイル入力モード時に内容を標準出力へ書き出す
  void writeCout();

  //すでに存在するresult.txtを上書きしないようにファイル名を作成する
  std::string makeNewFileName(const std::string& filename,bool enableCheck);

private:
  std::ofstream m_ofs;
  std::vector<std::string> m_inputs;
  std::vector<std::string> m_outputs;
};
