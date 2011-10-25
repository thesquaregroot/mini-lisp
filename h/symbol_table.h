#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <vector>
#include <map>
#include <string>
#include "./token.h"
#include "./var.h"

class symbol_table {
  private:
    std::vector<std::map<std::string, var> > vars;

  public:
    // Add another level to the stack.
    void push();
    // Remove the top of the stack.
    void pop();
    // Returns the value that the given variable name is bound to. 
    var get(std::string);
    // Create a binding of a variable name to a value in the top-most scope of the stack. 
    void set(std::string, std::string);
};

#endif
