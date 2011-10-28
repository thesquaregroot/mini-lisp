#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H 1

#include <vector>
#include <string>

class function_table {
  private:

  public:
    // Define a function with a name, parameters, and body
    void define(std::string, std::vector<std::string>, s_expression*);
    // Call a function with the given parameters
    s_expression* call(std::string, s_expression*);
}

#endif
