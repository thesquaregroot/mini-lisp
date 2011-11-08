#include <cctype>
#include "../h/tokenizer.h"
using namespace std;

// std::stream* ins;
// std::string buffer;
// char look_ahead;
// int line;


char tokenizer::next_non_ws() {
    char tmp;
    while (!ins->eof() && isspace(tmp = ins->get())) {
        if (tmp == '\n') {
            ++line;
        }
    }
    if (ins->eof()) {
        return '\0';
    } else {
        return tmp;
    }
}

// public
tokenizer::tokenizer() {
    ins = &cin;
}

tokenizer::tokenizer(istream* in) {
    ins = in;
}

token tokenizer::get() {
    token t;
    lookahead = next_non_ws();
    if (ins->eof()) {
        t.type = F_END;
        return t;
    }
    // if digit, test against 1, else use the actual lookhead
    //   this allows for a slight optimization after the +/- cases.
    switch(isdigit(lookahead)?'1':lookahead) {
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
        case '1':
            // expect a number afterward
            bool one_or_more = false;
            while (!ins->eof() && isdigit(lookahead = ins->get())) {
                t.lex_val += lookahead;
                one_or_more = true;
            }
            if (ins->eof()) {
                t.type = F_END;
                return t;
            } else {
                if ((isspace(lookahead) || lookahead == ')') && one_or_more) {
                    ins->unget();
                    t.type = ATOM;
                } else {
                    // invalid character or +/- without digits
                    t.lex_val += lookahead;
                    t.type = ERROR;
                }
            }
            break;
        default:
            if (isalpha(lookahead)) {
                t.lex_val += lookahead;
                while (!ins->eof() && isalnum(lookahead = ins->get())) {
                    t.lex_val += lookahead;
                }
                if (ins->eof()) {
                    t.type = F_END;
                } else {
                    if ((isspace(lookahead) || lookahead == ')') && one_or_more) {
                        ins->unget();
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

