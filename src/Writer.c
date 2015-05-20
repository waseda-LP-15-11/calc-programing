#include "Writer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
void Writer::writeOneLine()
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
 
void Writer::writeCout()
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

char* Writer::makeNewFileName(const std::string& filename,bool enableCheck)
{
	if(!enableCheck)
	{
		sprintf(szDst, "%s", filename.c_str());
		return szDst;
	}

	std::string newFileName = filename;

	//filenameがresult.txtならresult001.txtとする。
	const int pos = filename.rfind(".txt");
	newFileName.replace(pos,4,"001.txt");

	//ファイルの重複チェック
	for(int i = 1; i<1000 ;++i)
	{
		if(std::ifstream(newFileName))
		{
			//ファイルが開けた=そのファイル名は重複しているのでインクリメント
			std::ostringstream sout;
    		sout << std::setfill('0') << std::setw(3) << i;///"002"という0埋めした文字列ができる
    		newFileName.replace(pos,3,sout.str());
		}
		else
		{
			break;
		}
	}
    //const char* pszDst = strSrc.c_str();
    sprintf(szDst, "%s", newFileName.c_str());
	return szDst;
}