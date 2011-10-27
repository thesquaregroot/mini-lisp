#include <cctype>
#include "../h/tokenizer.h"
using namespace std;
// istream ins;
// char look_ahead;


tokenizer::tokenizer(istream* in) {
    this.ins = in;
}

token tokenizer::get() {
    token t;
    // skip whitespace
    while (!ins.eof() && isspace(lookahead = ins.get()));
    
    if (ins.eof()) {
        t.type = F_END;
    }
    switch(lookahead) {
        case '(':
            t.type = L_PAREN;
            t.lex_val = '(';
            break;
        case ')':
            t.type = R_PAREN;
            t.lex_val = ')';
            break;
        case '.':
            t.type = DOT;
            t.lex_val = '.';
            break;
        case '-':
        case '+':
            // save +/-
            t.lex_val += lookahead;
            // expect a number afterward
            bool one_or_more = false;
            while (!ins.eof() && isdigit(lookahead = ins.get())) {
                t.lex_val += lookahead;
                one_or_more = true;
            }
            if (ins.eof()) {
                t.type = F_END;
            } else {
                if ((isspace(lookahead) || lookahead == ')') && one_or_more) {
                    cin.unget();
                    t.type = ATOM;
                } else {
                    t.lex_val += lookahead;
                    t.type = ERROR;
                }
            }
            break;
        default:
            if (isalpha(lookahead)) {
                t.lex_val += lookahead;
                while (!ins.eof() && isalnum(lookahead = ins.get())) {
                    t.lex_val += lookahead;
                }
                if (ins.eof()) {
                    t.type = F_END;
                } else {
                    if ((isspace(lookahead) || lookahead == ')') && one_or_more) {
                        cin.unget();
                        t.type = ATOM;
                    } else {
                        t.lex_val += lookahead;
                        t.type = ERROR;
                    }
                }
            } else {
                t.lex_val += lookahead;
                t.type = ERROR;
            }
            break;
    }
    return t;
}

