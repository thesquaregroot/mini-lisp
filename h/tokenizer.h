#ifndef TOKENIZER_H
#define TOKENIZER_H 1

#include <iostream>
#include <string>
#include "token.h"

class tokenizer {
  private:
    std::istream* ins;
    std::string buffer;
    char look_ahead;
    int line;

  public:
    tokenizer();
    tokenizer(std::istream*);
    token get();
    int lineno();
};

#endif
