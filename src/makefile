TARGET = calc
BISON_SRC = $(TARGET).y
INCLUDE_BISON_C = variable.c print.c exmath.c Writer.c memory.c MemLeakChecker.c sum.c args.c numberBase.c
INCLUDE_BISON_O = variable.o print.o exmath.o Writer.o memory.o MemLeakChecker.o sum.o args.o numberBase.o
BISON_H   = $(TARGET).tab.h
BISON_C   = $(TARGET).tab.c
BISON_O   = $(TARGET).tab.o
BISON_OUT = $(BISON_C) $(BISON_H) $(TARGET).output
FLEX_SRC  = $(TARGET).l
FLEX_C    = lex.yy.cc
FLEX_O    = lex.yy.o
C_FILES   = $(BISON_C) $(FLEX_C) $(INCLUDE_BISON_C)
OBJ       = $(FLEX_O) $(BISON_O) $(INCLUDE_BISON_O)

all : $(TARGET)

$(TARGET) : $(OBJ)
	g++ -g -std=c++14 -o $@ $(OBJ)

$(FLEX_C) : $(FLEX_SRC) $(BISON_H)
	flex $(FLEX_SRC)

$(BISON_OUT) : $(BISON_SRC)
	bison -dv $(BISON_SRC)

.c.o :
	g++ -g -std=c++14 -c $<


clean :
	rm -f *.yy.cc
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.output
	rm -f *.o
	rm -f *.gch
	rm -f $(TARGET)

lex.yy.o: lex.yy.cc calc.tab.h sum.h exmath.h numberBase.h
calc.tab.o: calc.tab.c calc.tab.h variable.h print.h exmath.h Writer.h memory.h MemLeakChecker.h sum.h args.h numberBase.h
