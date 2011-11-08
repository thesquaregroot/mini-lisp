#ifndef TOKEN_H
#define TOKEN_H 1

#include <string>
#include "token_type.h"

struct token {
  std::string lex_val;
  token_type type;
};

#endif
