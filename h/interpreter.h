#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include "s_expression.h"
#include "tokenizer.h"

class interpreter {
  private:
    s_expression* get_exp();
    int eval_exp(s_expression*);
  public
    interpreter(tokenizer);
    bool exec();
};

#endif
