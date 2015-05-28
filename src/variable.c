#include "variable.h"
#include "calc.hpp"

// 変数の値を表示する
//void show_variable(const char* name)
//{
//	if(double* value = get_value(name))
//	{
//		Println(string(name)+" = "+to_String(*value));
//	}
//}

// 変数を作成
void add_variable(const char* name, Value *var)
{
	Variables[to_String(name)].u.num_value = var->u.num_value;
//	Println(string(name)+" = "+to_String(value));
}

void remove_variable(const char *name) {
	Variables.erase(to_String(name));
}

//void update_ans(double value)
//{
//	variables["ans"] = value;
//}

// 名前がnameの変数を取得する。
Value* search_local_variable(const char* name)
{
	const string key = to_String(name);
	if (Variables.find(key) != Variables.end())
	{
		return &Variables[key];
	}
	else
	{
//		Println("ERROR:: " + string(name) + " is undefined");
		return nullptr;
	}
}


//void dispVar(void)
//{
//	if(variables.empty())
//	{
//		Println("Variable is undefined");
//		return;
//	}
//	for(const auto& var: variables)
//	{
//		//var.firstがキー(変数名),var.secondが変数の値
//		Println(var.first + " = " + to_String(var.second));
//	}
//}