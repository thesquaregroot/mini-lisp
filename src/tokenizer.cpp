#include <cctype>
#include "../h/tokenizer.h"
using namespace std;
// istream ins;
// string buffer;
// char look_ahead;


tokenizer::tokenizer(istream* in) {
    this.ins = in;
}

token tokenizer::get() {
    // skip whitespace
    while (isspace(lookahead = ins.get()));


    return ERROR;
}
