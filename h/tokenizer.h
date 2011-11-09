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
    bool verbose;

    // get the next non-whitespace character from the stream
    char next_non_ws();

  public:
    // Create a tokenizer defaulting on standard input.
    tokenizer(bool = false);
    // Create a tokenizer with the given input stream.
    tokenizer(std::istream*);

    // Get the next token from the input stream.
    token get();
    // Get the current line number.
    int lineno();
};

#endif
