#include "../h/itos.h"
#include "../h/interpreter.h"
using namespace std;

// symbol_table symbols;
// tokenizer ins;
// token err_tkn;
// std::string err_msg;

/// private
s_expression* interpreter::get_exp(token start) {
    if (start.type != L_PAREN && start.type != ATOM) {
        err_tkn = start;
        err_msg = "Program must start with a '(' or an atom.";
        return NULL;
    }
    if (start.type == ATOM) {
        // just an atom, nothing more to do
        s_expression* s = new s_expression(start);
        return s;
    }
    // open paren, handle list
    token t = ins.get();
    s_expression* s = get_list(t);
    if (s == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }
    // have list, get close paren
    t = ins.get();
    if (t.type != R_PAREN) {
        err_tkn = t;
        err_msg = "Expression didn't end with closing parenthesis.";
        return NULL;
    }
    // return the list
    return s;
}

s_expression* interpreter::get_list(token start) {
    if (start.type == R_PAREN) {
        // empty string case
        s_expression* s = new s_expression(token(ATOM, "NIL"));
        return s;
    }
    if (start.type != ATOM && start.type != L_PAREN) {
        // ERROR or F_END
        err_tkn = start;
        err_msg = "Invalid beginning of list.";
        return NULL;
    }
    token t = ins.get();
    s_expression* s = get_exp(t);
    if (s == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }  
    t = ins.get();
    s_expression* l;
    switch(t.type) {
        case R_PAREN:
            // done with this list
            return s;
            break;
        case DOT:
            // ignore dot
            t = ins.get();
            if (t.type != ATOM && t.type != L_PAREN) {
                err_tkn = t;
                err_msg = "Non-list following '.'.";
                return NULL;
            }
        case ATOM:
        case L_PAREN:
            // get a list
            l = get_list(t);
            if (l == NULL) {
                // Error found in other function, no need to do anything
                return NULL;
            }
            // combine s-expressions
            return new s_expression(s, l);
            break;
        default:
            err_tkn = t;
            err_msg = "Invalid list element.";
            return NULL;
            break;
    }
    // shouldn't get here
    err_tkn = t;
    err_msg = "Unknown error.";
    return NULL;
}

/// public
interpreter::interpreter(tokenizer& tokens) {
    ins = tokens;
}

bool interpreter::exec() {
    return false;
}

string interpreter::error() {
    if (err_tkn.type == F_END) {
        // override error message in this case
        err_msg = "Unexpected end of file.";
    }
    return ("ERROR: line " + itos(ins.lineno()) + ": " + err_msg);
}

