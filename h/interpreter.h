#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include <vector>
#include <set>
#include <string>
#include "symbol_table.h"
#include "s_expression.h"
#include "tokenizer.h"

class interpreter {
  private:
    symbol_table symbols;
    tokenizer ins;
    token* err_tkn;
    std::string err_msg;
    std::set<std::string> *keywords;

    // Evalutate an s_expression
    s_expression* eval(s_expression*);
    // Build an s_expression out of the string of tokens
    s_expression* get_expr(token);
    // Get a 'list' within an expression.
    //   This is related to the revised grammar.
    //   See README for more details.
    s_expression* get_list(token);

  public:
    // construct with a tokenizer
    interpreter(tokenizer&);
    // Properly dispose of stack memory
    ~interpreter();

    // interpret the code
    bool exec();
    // build an error string
    //   only valid if exec() returns false
    std::string error();
};

#endif
