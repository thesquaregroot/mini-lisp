#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include <vector>
#include <string>
#include "symbol_table.h"
#include "funciton_table.h"
#include "tokenizer.h"

class interpreter {
  private:
    symbol_table symbols;
    function_table funcs;
    tokenizer* ins;

    std::string err_msg;

    // Build an s_expression out of the string of tokens
    s_expression get_exp();
    // Get the parameters to a funciton definition
    //   Called by get_exp
    std::vector<std::string> get_params();

  public
    // construct with a tokenizer
    interpreter(tokenizer*);
    // interpret the code
    bool exec();
    // build an error string
    //   only valid if exec() returns false
    std::string error();
};

#endif
