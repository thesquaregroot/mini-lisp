#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <vector>
#include <map>
#include <string>
#include "s_expression.h"
#include "definition.h"

class symbol_table {
  private:
    // variables
    std::vector<std::map<std::string, s_expression*> > vars;
    // functions
    std::map<definition, s_expression*> funcs;

  public:
    // Add another level to the stack.
    void push();
    // Remove the top of the stack.
    void pop();

    // Returns the value that the given variable name is bound to. 
    s_expression* get(std::string&);
    // Create a binding of a variable name to a value in the top-most scope of the stack. 
    void set(std::string&, s_expression*);

    // Define a function with a name, parameters, and body
    void define(std::string&, s_expression*, s_expression*);
    /* Returns the arguments and boyd of a function with the given name and number of arguments
    //  in the following structure of s-expression:
    //     .
    //    / \
    // args body
    */
    s_expression* retrieve(std::string&, int);
};

#endif
