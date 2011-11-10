#include <cctype>
#include "../h/tokenizer.h"
using namespace std;

// std::stream* ins;
// std::string buffer;
// char look_ahead;
// int line;
// bool verbose


char tokenizer::next_non_ws() {
    char tmp;
    while (!ins->eof() && isspace(tmp = toupper(ins->get()))) {
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

char tokenizer::next() {
    return toupper(ins->get());
}

// public
tokenizer::tokenizer(bool vrbs) {
    ins = &cin;
    line = 1;
    verbose = vrbs;
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
        if (verbose) cout << "F_END\n";
        return t;
    }
    // if digit, test against 1, else use the actual lookhead
    //   this allows for a slight optimization after the +/- cases.
    switch(isdigit(look_ahead)?'1':look_ahead) {
        case '(':
            t.type = L_PAREN;
            if (verbose) cout << "L_PAREN\n";
            t.lex_val = '(';
            break;
        case ')':
            t.type = R_PAREN;
            if (verbose) cout << "R_PAREN\n";
            t.lex_val = ')';
            break;
        case '.':
            t.type = DOT;
            t.lex_val = '.';
            if (!isspace(look_ahead = next())) {
                t.lex_val += look_ahead;
                if (verbose) cout << "ERROR\n";
                t.type = ERROR;
                // don't worry about putting it back since it's just whitespace
            }
            break;
        case '-':
        case '+':
            // save +/-
            t.lex_val += look_ahead;
        case '1':
            if (isdigit(look_ahead)) {
                t.lex_val += look_ahead;

                while (!ins->eof() && isdigit(look_ahead = next())) {
                    t.lex_val += look_ahead;
                }
                if (isspace(look_ahead) || look_ahead == ')' || ins->eof()) {
                    // return the extra character if not at the end of the stream
                    if (!ins->eof()) ins->unget();
                    // We have an INT
                    if (verbose) cout << "ATOM\n";
                    t.type = ATOM;
                } else {
                    // invalid character after number or +/- without digits
                    t.lex_val += look_ahead;
                    if (verbose) cout << "ERROR\n";
                    t.type = ERROR;
                }
            } else {
                // invalid character after number or +/- without digits
                t.lex_val += look_ahead;
                if (verbose) cout << "ERROR\n";
                t.type = ERROR;
            }
            break;
        default:
            if (isalpha(look_ahead)) {
                t.lex_val += look_ahead;

                while (!ins->eof() && isalnum(look_ahead = next())) {
                    t.lex_val += look_ahead;
                }
                if (isspace(look_ahead) || look_ahead == ')' || ins->eof()) {
                    // return the extra character if not at the end of the stream
                    if (!ins->eof()) ins->unget();
                    // we have an identifier (function call)
                    if (verbose) cout << "ATOM\n";
                    t.type = ATOM;
                } else {
                    // invalid identifier
                    t.lex_val += look_ahead;
                    if (verbose) cout << "ERROR\n";
                    t.type = ERROR;
                }
            } else {
                // Invalid character
                t.lex_val += look_ahead;
                if (verbose) cout << "ERROR\n";
                t.type = ERROR;
            }
            break;
    }
    return t;
}

int tokenizer::lineno() {
    return line;
}

