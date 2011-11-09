#ifndef TOKEN_H
#define TOKEN_H 1

#include <string>
#include "token_type.h"

struct token {
    token_type type;
    std::string lex_val;

    token();
    token(token_type, std::string);
};

#endif
