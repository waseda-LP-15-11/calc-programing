#set(CMAKE_VERBOSE_MAKEFILE 1)

cmake_minimum_required(VERSION 3.2)
project(calc_programing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser src/calc.y ${CMAKE_SOURCE_DIR}/src/calc.tab.c [] [-dv])
FLEX_TARGET(MyScanner src/calc.l  ${CMAKE_SOURCE_DIR}/src/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES
    src/exmath.c
    src/memory.c
    src/print.c
    src/Writer.c
    src/sum.c
    src/args.c
    src/numberBase.c
    src/lexer.cpp
    src/variable.c
    src/calc.tab.c)

SET_SOURCE_FILES_PROPERTIES(
 src/exmath.c
 src/memory.c
 src/print.c
 src/variable.c
 src/Writer.c
 src/sum.c
 src/args.c
 src/numberBase.c
 src/calc.tab.c
 PROPERTIES LANGUAGE CXX )

add_executable(calc_programing
    ${SOURCE_FILES}
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS} src/create.h src/create.cpp src/eval.h src/eval.cpp)
