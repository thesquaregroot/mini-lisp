#include "../h/itos.h"
#include "../h/interpreter.h"
using namespace std;

// symbol_table symbols;
// tokenizer ins;
// token err_tkn;
// std::string err_msg;

/// private
s_expression* interpreter::get_expr(token start) {
    if (start.type != L_PAREN && start.type != ATOM) {
        err_tkn = start;
        err_msg = "Invalid list element.";
        return NULL;
    }
    if (start.type == ATOM) {
        // just an atom, nothing more to do
        s_expression* s = new s_expression(start);
        return s;
    }
    // open paren, handle list
    s_expression* s = get_list(ins.get());
    if (s == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }
    // list has found close paren
    // return the list
    return s;
}

s_expression* interpreter::get_list(token start) {
    if (start.type == R_PAREN) {
        // empty string case
        return new s_expression(token(ATOM, "NIL"));
    }
    s_expression* s = get_expr(start);
    if (s == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }
    token t = ins.get();
    s_expression* l;
    // either end or followed by another list
    switch(t.type) {
        case ERROR:
            err_tkn = start;
            err_msg = "Unrecognized token.";
            return NULL;
            break;
        case R_PAREN:
            // end of list
            return s;
            break;
        case DOT:
            // ignore dot and continue to list
            t = ins.get();
        default:
            // combine s with following list
            // error catching will happen at the beginning of the function
            l = get_list(t);
            if (l == NULL) {
                // Error found in other function, no need to do anything
                return NULL;
            }
            return s->append_right(l);
            break;
    }
    return NULL; // will never get here, this just shuts up the compiler
}

/// public
interpreter::interpreter(tokenizer& tokens) {
    ins = tokens;
}

bool interpreter::exec() {
    token t = ins.get();
    while (t.type != F_END) {
        s_expression* s = get_expr(t);
        if (s == NULL) {
            // error
           return false;
        }
        cout << s->to_string() << endl;
        t = ins.get();
    }
    return true;
}

string interpreter::error() {
    if (err_tkn.type == F_END) {
        // override error message in this case
        err_msg = "Unexpected end of file.";
    }
    return ("ERROR: At token `" + err_tkn.lex_val + "` on line " + itos(ins.lineno()) + ": " + err_msg);
}

