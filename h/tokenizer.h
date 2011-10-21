#ifndef TOKENIZER_H
#define TOKENIZER_H 1

#include <string>
#include "token.h"

class tokenizer {
  private:
    std::string buffer;
    char look_ahead;

  public:
    token get();
};

#endif
