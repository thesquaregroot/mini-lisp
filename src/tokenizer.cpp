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
    line = 1;
}

tokenizer::tokenizer(istream* in) {
    ins = in;
    line = 1;
}

token tokenizer::get() {
    token t;
    look_ahead = next_non_ws();
    if (ins->eof()) {
        t.type = F_END;
        return t;
    }
    bool one_or_more = false;
    // if digit, test against 1, else use the actual lookhead
    //   this allows for a slight optimization after the +/- cases.
    switch(isdigit(look_ahead)?'1':look_ahead) {
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
            t.lex_val += look_ahead;
        case '1':
            // expect a number afterward
            while (!ins->eof() && isdigit(look_ahead = ins->get())) {
                t.lex_val += look_ahead;
                one_or_more = true;
            }
            if ((isspace(look_ahead) || look_ahead == ')' || ins->eof()) && one_or_more) {
                // return the extra character if not at the end of the stream
                if (ins->eof()) ins->unget();
                // We have an INT
                t.type = ATOM;
            } else {
                // invalid character after number or +/- without digits
                t.lex_val += look_ahead;
                t.type = ERROR;
            }
            break;
        default:
            if (isalpha(look_ahead)) {
                t.lex_val += look_ahead;
                while (!ins->eof() && isalnum(look_ahead = ins->get())) {
                    t.lex_val += look_ahead;
                }
                if ((isspace(look_ahead) || look_ahead == ')' || ins->eof()) && one_or_more) {
                    // return the extra character if not at the end of the stream
                    if (ins->eof()) ins->unget();
                    // we have an identifier (function call)
                    t.type = ATOM;
                } else {
                    // invalid identifier
                    t.lex_val += look_ahead;
                    t.type = ERROR;
                }
            } else {
                // Invalid character
                t.lex_val += look_ahead;
                t.type = ERROR;
            }
            break;
    }
    return t;
}

int tokenizer::lineno() {
    return line;
}

