#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H 1

#include <vector>
#include <string>
#include "./symbol_table.h"
#include "./s_expression.h"

class function_table {
  private:
    std::map<std::string, vector<std::string> > params;
    std::map<std::string, s_expression> bodies;

  public:
    // Define a function with a name, parameters, and body
    void define(std::string, std::vector<std::string>&, s_expression&);
    // Call a function with the given parameters and enviroment
    s_expression* call(std::string, s_expression&, symbol_table&);
}

#endif
