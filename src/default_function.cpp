//
// Created by Keigo Ogawa on 5/22/15.
//

#include "default_function.h"
#include "calc.hpp"

void defineDefaultFunction(const char *name) {
    char* parme = "x";
    char *math_name = (char*)name;
    ParameterList* parameter = create_parameter(parme);
    Expression* math_expression = create_math_expression(math_name);
    Expression* expression_list = create_expression_list(math_expression);

    function_define(math_name, parameter, expression_list);
}

void defineAllDefaultFunction() {
    defineDefaultFunction("sin");
    defineDefaultFunction("cos");
    defineDefaultFunction("tan");
    defineDefaultFunction("sinh");
    defineDefaultFunction("cosh");
    defineDefaultFunction("tanh");
    defineDefaultFunction("asin");
    defineDefaultFunction("acos");
    defineDefaultFunction("atan");
    defineDefaultFunction("asinh");
    defineDefaultFunction("acosh");
    defineDefaultFunction("atanh");
    defineDefaultFunction("exp");
    defineDefaultFunction("exp2");
    defineDefaultFunction("log2");
    defineDefaultFunction("log10");
    defineDefaultFunction("log");
    defineDefaultFunction("ln");
    defineDefaultFunction("abs");
    defineDefaultFunction("sqrt");
    defineDefaultFunction("cbrt");
    defineDefaultFunction("round");
    defineDefaultFunction("rint");
    defineDefaultFunction("floor");
    defineDefaultFunction("ceil");
    defineDefaultFunction("Radians");
    defineDefaultFunction("Degrees");
    defineDefaultFunction("toBin");
    defineDefaultFunction("toHex");
//    defineDefaultFunction("");
}