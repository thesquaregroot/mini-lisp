#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <vector>
#include <map>
#include <string>
#include "s_expression.h"
#include "token.h"

class symbol_table {
  private:
    // variables
    std::vector<std::map<std::string, s_expression*> > vars;
    // functions
    std::map<std::string, std::vector<std::string> > params;
    std::map<std::string, s_expression*> bodies;

  public:
    // Add another level to the stack.
    void push();
    // Remove the top of the stack.
    void pop();

    // Returns the value that the given variable name is bound to. 
    s_expression* get(std::string);
    // Create a binding of a variable name to a value in the top-most scope of the stack. 
    void set(std::string, s_expression*);

    // Define a function with a name, parameters, and body
    void define(std::string, std::vector<std::string>&, s_expression*);
    // Call a function with the given parameters and enviroment
    s_expression* call(std::string, s_expression*, symbol_table&);
};

#endif
