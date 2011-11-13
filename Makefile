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
OBJS = o/definition.o o/interpreter.o o/itos.o  o/main.o  o/s_expression.o o/symbol_table.o o/token.o o/tokenizer.o

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>. Variable
# "$@" stands for the current target. 

$(EXE) : $(OBJS) # depends on all object files
	$(CXX) $^ -o $@

# An object file is dependent on the corresponding source file

o/%.o : src/%.cpp
	mkdir -p o
	$(COMPILE) -o $@ $<

clean:
	rm -f o/*.o ./$(EXE)
	rmdir o

# DO NOT DELETE

src/definition.o: h/definition.h
src/interpreter.o: h/itos.h h/interpreter.h h/symbol_table.h h/s_expression.h
src/interpreter.o: h/var_type.h h/token.h h/token_type.h h/definition.h
src/interpreter.o: h/tokenizer.h
src/itos.o: h/itos.h
src/main.o: h/interpreter.h h/symbol_table.h h/s_expression.h h/var_type.h
src/main.o: h/token.h h/token_type.h h/definition.h h/tokenizer.h
src/s_expression.o: h/itos.h h/s_expression.h h/var_type.h h/token.h
src/s_expression.o: h/token_type.h
src/symbol_table.o: h/symbol_table.h h/s_expression.h h/var_type.h h/token.h
src/symbol_table.o: h/token_type.h h/definition.h
src/token.o: h/token.h h/token_type.h
src/tokenizer.o: /usr/include/unistd.h /usr/include/_types.h
src/tokenizer.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
src/tokenizer.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
src/tokenizer.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
src/tokenizer.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_structs.h
src/tokenizer.o: /usr/include/sys/_select.h h/tokenizer.h h/token.h
src/tokenizer.o: h/token_type.h
h/interpreter.o: h/symbol_table.h h/s_expression.h h/var_type.h h/token.h
h/interpreter.o: h/token_type.h h/definition.h h/tokenizer.h
h/s_expression.o: h/var_type.h h/token.h h/token_type.h
h/symbol_table.o: h/s_expression.h h/var_type.h h/token.h h/token_type.h
h/symbol_table.o: h/definition.h
h/token.o: h/token_type.h
h/tokenizer.o: h/token.h h/token_type.h
