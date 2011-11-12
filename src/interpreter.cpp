#include "../h/itos.h"
#include "../h/interpreter.h"
using namespace std;

// symbol_table symbols;
// tokenizer ins;
// token* err_tkn;
// std::string err_msg;

/// private

s_expression* interpreter::eval(s_expression* s) {
    s_expression *r = NULL;

    if (s->is_leaf()) {
        if (s->type() == IDENT) {
            // look up identifier
            string str = s->to_string();
            r = symbols.get(str);
        } else {
            // echo numbers and booleans
            r = s;
        }
    } else {
        // Test for leaf with function name
        if (!s->is_list()) {
            err_msg = "Input must be a string of lists.";
            return NULL;

        } else {
            // evalute the s_expression
            string exp = (*s)[0]->to_string();

            if (exp == "CAR") {               // CAR
                if (s->size() != 2) {
                    err_msg = "CAR: Expected 1 argument, recieved " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = eval((*s)[1]);
                if (r->is_leaf()) {
                    err_msg = "CAR: Exepected a list, recieved an atom.";
                    return NULL;
                }
                r = r->car();

            } else if (exp == "CDR") {        // CAR
                

            } else if (exp == "CONS") {       // CONS

            } else if (exp == "EQ") {         // EQ

            } else if (exp == "NULL") {       // NULL

            } else if (exp == "INT") {        // INT

            } else if (exp == "PLUS") {       // PLUS

            } else if (exp == "MINUS") {      // MINUS
                
            } else if (exp == "QUOTIENT") {   // QUOTIENT
                
            } else if (exp == "REMAINDER") {  // REMAINDER
                
            } else if (exp == "LESS") {       // LESS
                
            } else if (exp == "GREATER") {    // GREATER
                
            } else if (exp == "COND") {       // COND
                
            } else if (exp == "QUOTE") {      // QUOTE
                
            } else if (exp == "DEFUN") {      // DEFUN
                
            } else {                          // USER-DEFINED FUNCTION CALL
                // lookup in symbol table
                                
            }
        }
    }
    return r;
}

s_expression* interpreter::get_expr(token start) {
    if (start.type != L_PAREN && start.type != ATOM) {
        err_tkn = new token(start);
        err_msg = "Invalid list element.";
        return NULL;
    }
    if (start.type == ATOM) {
        // just an atom, nothing more to do
        s_expression *s = new s_expression(start);
        return s;
    }
    token t = ins.get();
    if (t.type == R_PAREN) {
        // empty string case
        return new s_expression(token(ATOM, "NIL"));
    }
    // get first expression
    s_expression *s = get_expr(t);
    if (s == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }
    t = ins.get();
    s_expression *r, *p;
    switch (t.type) {
        case ERROR:
            err_tkn = new token(t);
            err_msg = "Unrecognized token.";
            return NULL;
            break;
        case R_PAREN:
            p = new s_expression();
            p->car() = s;
            return p;
            break;
        default:
            // DOT, L_PAREN, ATOM
            if (t.type == DOT) {
                r = get_expr(ins.get());
                // must be end of expression
                t = ins.get();
                if (t.type != R_PAREN) {
                    err_tkn = new token(t);
                    err_msg = "Invalid use of dot operator.";
                    return NULL;
                }
            } else {
                r = get_list(t);
            }
            if (r == NULL) {
                // Error found in other function, no need to do anything
                return NULL;
            }

            p = new s_expression();
            p->car() = s;
            p->cdr() = r;
            return p;
            break;
    }
    // list has found close paren
    // return the list
    return s;
}

s_expression* interpreter::get_list(token start) {
    s_expression *s = new s_expression();
    s->car() = get_expr(start);
    if (s->car() == NULL) {
        // Error found in other function, no need to do anything
        return NULL;
    }

    token t = ins.get();
    s_expression *r;
    // either end or followed by another list
    switch(t.type) {
        case ERROR:
        case DOT:
            err_tkn = new token(t);
            if (t.type == DOT) {
                err_msg = "Invalid use of dot operator.";
            } else { // ERROR
                err_msg = "Unrecognized token.";
            }
            return NULL;
            break;
        case R_PAREN:
            // end of list
            return s;
            break;
        default:
            // ATOM, L_PAREN
            r = get_list(t);
            if (r == NULL) {
                // Error found in other function, no need to do anything
                return NULL;
            }
            s->cdr() = r;
            return s;
        break;
    }
    return NULL; // will never get here, this just shuts up the compiler
}

/// public
interpreter::interpreter(tokenizer& tokens) {
    ins = tokens;
    err_tkn = NULL;
}

interpreter::~interpreter() {
    delete err_tkn;
}

bool interpreter::exec() {
    token t = ins.get();
    while (t.type != F_END) {
    //    ins.print_prompt();

        s_expression* s = get_expr(t);
        if (s == NULL) {
            // error
           return false;
        }
        // evaluate
        s = eval(s);
        if (s == NULL) {
            // error
            return false;
        }
        // print result
        cout << s->to_string() << endl;

        // get beginning of next expression (or EOF).
        t = ins.get();
    }
    return true;
}

string interpreter::error() {
    string s = "ERROR: ";
    if (err_tkn != NULL) {
        if (err_tkn->type == F_END) {
            // override error message in this case
            err_msg = "Unexpected end of file.";
        }
        // only show token if it is related to the error
        s += "At token `" + err_tkn->lex_val + "` on line " + itos(ins.lineno()) + ": ";

    } else {
        // otherwise just display the line number
        s += "On line " + itos(ins.lineno()) + ": ";
    }
    s += err_msg;
    return s;
}

