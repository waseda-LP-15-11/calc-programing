
#include "variable.h"
#include "print.h"
#include <map>
using namespace std;


static map<string,double> variables;

// 変数の値を表示する
void show_variable(const char* name) 
{
	if(double* value = get_value(name))
	{
		Println(string(name)+" = "+to_String(*value));
	}
}

// 変数を更新もしくは作成
void update_variable(const char* name, double value) 
{
	variables[to_String(name)] = value;	
	Println(string(name)+" = "+to_String(value));
}

void update_ans(double value)
{
	variables["ans"] = value;
}

// 名前がnameの変数を取得する。
double* get_value(const char* name) 
{
	const string key = to_String(name);
	if (variables.find(key) != variables.end())
	{
		return &variables[key];
	}
	else
	{
		Println("ERROR:: " + string(name) + " is undefined");
		return nullptr;
	}
}


void dispVar(void)
{
	if(variables.empty())
	{
		Println("Variable is undefined");
		return;
	}
	for(const auto& var: variables)
	{
		//var.firstがキー(変数名),var.secondが変数の値
		Println(var.first + " = " + to_String(var.second));
	}
}