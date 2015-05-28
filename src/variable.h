#pragma once
#include "calc.hpp"
//void show_variable(const char* name);
void add_variable(const char*  name, Value *var);
//void update_ans(double value);
Value* search_local_variable(const char* name);
//void dispVar(void);
void remove_variable(const char *name);