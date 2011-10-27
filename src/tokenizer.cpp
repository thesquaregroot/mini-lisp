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
    token t;
    buffer.clear();
    // skip whitespace
    while (!ins.eof() && isspace(lookahead = ins.get()));
    
    if (ins.eof()) {
        t.type = F_END;
    }
    switch(lookahead) {
        case '(':
            t.type = L_PAREN;
            break;
        case ')':
            t.type = R_PAREN;
            break;
        case '.':
            t.type = DOT;
            break;
        case '-':
        case '+':
            // save +/-
            buffer += lookahead;
            // expect a number afterward
            while (!ins.eof() && isdigit(lookahead = ins.get())) {
                buffer += lookahead;
            }
            if (isspace(lookahead) || lookahead == ')') {
                t.type = ATOM;
            }
            break;
        default: {
            if (isalpha(lookahead)) {
                
            }
            break;
    }
    return ERROR;
}

