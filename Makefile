# This is a very simple makefile for building the Lisp interpreter
# project when using C++ on stdsun. Feel free to add any improvements:
# e.g. pattern rules, automatic tracking of dependencies, etc. There
# is a lot of info about "make" on the web.

# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -g -Wall

# Creating a .o file
COMPILE = $(CXX) $(CXXFLAGS) -c

# Name of the executable; should match the contents of Runfile
EXE = lisp

# All object files
OBJS = src/interpreter.o  src/itos.o  src/main.o  src/s_expression.o src/symbol_table.o src/tokenizer.o

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>. Variable
# "$@" stands for the current target. 

$(EXE) : $(OBJS) # depends on all object files
	$(CXX) $^ -o $@

# An object file is dependent on the corresponding source file

src/%.o : src/%.cpp
	$(COMPILE) -o $@ $<

clean:
	rm -f src/*.o ./lisp

# DO NOT DELETE

src/interpreter.o: h/itos.h h/interpreter.h h/symbol_table.h
src/interpreter.o: h/./s_expression.h h/./var_type.h h/./token.h
src/interpreter.o: h/./token_type.h h/./token.h h/tokenizer.h
src/itos.o: h/itos.h
src/main.o: h/interpreter.h h/symbol_table.h h/./s_expression.h
src/main.o: h/./var_type.h h/./token.h h/./token_type.h h/./token.h
src/main.o: h/tokenizer.h
src/s_expression.o: h/s_expression.h h/symbol_table.h h/./s_expression.h
src/s_expression.o: h/./var_type.h h/./token.h h/./token_type.h h/./token.h
src/symbol_table.o: h/symbol_table.h h/./s_expression.h h/symbol_table.h
src/symbol_table.o: h/./token.h h/./var_type.h h/./token.h h/./token_type.h
src/tokenizer.o: h/tokenizer.h h/./token.h h/./token_type.h
