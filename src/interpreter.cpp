#include <unistd.h>
#include <cstdio>
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
            if (r == NULL) {
                err_msg = "A value for identifier '" + str + "' could not be resolved.";
                return NULL;
            }
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

            if (exp == "CAR") {               // CAR //
                if (s->size() != 2) {
                    err_msg = "CAR: Expected 1 argument, recieved " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = eval((*s)[1]);
                if (r == NULL) {
                    // error
                    return NULL;
                }
                if (r->is_leaf()) {
                    err_msg = "CAR: Exepected a list, recieved an atom.";
                    return NULL;
                }
                r = r->car();

            } else if (exp == "CDR") {        // CDR //
                if (s->size() != 2) {
                    err_msg = "CDR: Expected 1 argument, recieved " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = eval((*s)[1]);
                if (r == NULL) {
                    // error
                    return NULL;
                }
                if (r->is_leaf()) {
                    err_msg = "CDR: Exepected a list, recieved an atom.";
                    return NULL;
                }
                r = r->cdr();
                if (r == NULL) {
                    r = new s_expression(token(ATOM, "NIL"));
                }

            } else if (exp == "CONS") {       // CONS //
                if (s->size() != 3) {
                    err_msg = "CONS: Expeceted 3 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression* s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                s_expression* s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                r = new s_expression();
                r->car() = s1;
                r->cdr() = s2;

            } else if (exp == "ATOM") {       // ATOM //
                if (s->size() != 2) {
                    err_msg = "ATOM: Expeceted 1 argument, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = (*s)[1];
                if (r->is_leaf()) {
                    r = new s_expression(token(ATOM, "T"));
                } else {
                    r = new s_expression(token(ATOM, "NIL"));
                }

            } else if (exp == "EQ") {         // EQ //
                if (s->size() != 3) {
                    err_msg = "EQ: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf()) {
                    err_msg = "EQ: Argument 1 is not an atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf()) {
                    err_msg = "EQ: Argument 2 is not an atom.";
                    return NULL;
                }
                if (*s1 == *s2) {
                    r = new s_expression(token(ATOM, "T"));
                } else {
                    r = new s_expression(token(ATOM, "NIL"));
                }

            } else if (exp == "NULL") {       // NULL //
                if (s->size() != 2) {
                    err_msg = "NULL: Expeceted 1 argument, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = (*s)[1];
                if (r->is_null()) {
                    r = new s_expression(token(ATOM, "T"));
                } else {
                    r = new s_expression(token(ATOM, "NIL"));
                }

            } else if (exp == "INT") {        // INT //
                if (s->size() != 2) {
                    err_msg = "INT: Expeceted 1 argument, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = (*s)[1];
                if (r->type() == INT) {
                    r = new s_expression(token(ATOM, "T"));
                } else {
                    r = new s_expression(token(ATOM, "NIL"));
                }

            } else if (exp == "PLUS") {       // PLUS //
                if (s->size() != 3) {
                    err_msg = "PLUS: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "PLUS: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "PLUS: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, itos(s1->value() + s2->value())));

            } else if (exp == "MINUS") {      // MINUS //
                if (s->size() != 3) {
                    err_msg = "MINUS: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "MINUS: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "MINUS: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, itos(s1->value() - s2->value())));

            } else if (exp == "TIMES") {      // TIMES //
                if (s->size() != 3) {
                    err_msg = "TIMES: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "TIMES: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "TIMES: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, itos(s1->value() * s2->value())));

            } else if (exp == "QUOTIENT") {   // QUOTIENT //
                if (s->size() != 3) {
                    err_msg = "QUOTIENT: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "QUOTIENT: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "QUOTIENT: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, itos(s1->value() / s2->value())));

            } else if (exp == "REMAINDER") {  // REMAINDER //
                if (s->size() != 3) {
                    err_msg = "REMAINDER: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "REMAINDER: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "REMAINDER: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, itos(s1->value() % s2->value())));

            } else if (exp == "LESS") {       // LESS //
                if (s->size() != 3) {
                    err_msg = "LESS: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "LESS: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "LESS: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, (s1->value() < s2->value())?"T":"NIL" ) );

            } else if (exp == "GREATER") {    // GREATER //
                if (s->size() != 3) {
                    err_msg = "GREATER: Expeceted 2 arguments, received " + itos(s->size()-1) + ".";
                    return NULL;
                }
                s_expression *s1 = eval((*s)[1]);
                if (s1 == NULL) {
                    // error
                    return NULL;
                }
                if (!s1->is_leaf() || s1->type() != INT) {
                    err_msg = "GREATER: Argument 1 is not a numeric atom.";
                    return NULL;
                }
                s_expression *s2 = eval((*s)[2]);
                if (s2 == NULL) {
                    // error
                    return NULL;
                }
                if (!s2->is_leaf() || s2->type() != INT) {
                    err_msg = "GREATER: Argument 2 is not a numeric atom.";
                    return NULL;
                }
                r = new s_expression(token(ATOM, (s1->value() > s2->value())?"T":"NIL" ) );

            } else if (exp == "COND") {       // COND //
                if (s->size() == 1) {
                    err_msg = "COND: No arguments given.";
                    return NULL;
                }
                for (int i=1; i<s->size(); i++) {
                    s_expression* c = (*s)[i];
                    if (!c->is_list() || c->size() != 2) {
                        err_msg = "COND: Argument " + itos(i) + " is not a list of size two.";
                        return NULL;
                    }
                    r = eval(c->car());
                    if (r == NULL) {
                        // error
                        return NULL;
                    }
                    if (r->to_string() == "T") {
                        // expression becomes the second element of this list
                        r = eval(c->cdr()->car());
                        if (r == NULL) {
                            // error
                            return NULL;
                        }
                        break;  // exit
                    }
                    // else, go to next argument
                    if (i == s->size()-1) {
                        // none have evaluated to true
                        err_msg = "COND: No arguments evaluated to true.";
                        return NULL;
                    }
                }

            } else if (exp == "QUOTE") {      // QUOTE //
                if (s->size() != 2) {
                    err_msg = "QUOTE: Expected 1 argument, recieved " + itos(s->size()-1) + ".";
                    return NULL;
                }
                // nothing to do or check!
                r = (*s)[1];

            } else if (exp == "DEFUN") {      // DEFUN //
                if (s->size() != 4) {
                    err_msg = "DEFUN: Expected 4 arguments, recieved " + itos(s->size()-1) + ".";
                    return NULL;
                }
                r = (*s)[1];
                if (!r->is_leaf() || r->type() == INT) {
                    err_msg = "DEFUN: Invalid function name.";
                    return NULL;
                }
                string f_name = r->to_string();
                // check name
                if (keywords->count(f_name) > 0) {
                    err_msg = "DEFUN: '" + f_name + "' is a keyword.";
                    return NULL;
                }
                s_expression* args = (*s)[2];
                if (!args->is_list()) {
                    err_msg = "DEFUN: Expected argument 2 to be a list of argument names.";
                    return NULL;
                }
                // check the constaints on arguments
                set<string> arg_names;
                for (int i=0; i<args->size(); i++) {
                    s_expression *arg = (*args)[i];

                    if (!arg->is_leaf() || arg->type() == BOOL) {
                        err_msg = "DEFUN: Formal " + itos(i+1) + " in '" + f_name + "' is not a valid identifier.";
                        return NULL;
                    }
                    if (arg_names.count(arg->to_string()) > 0) {
                        err_msg = "DEFUN: Formal '" + arg->to_string() + "' repeated in definition of '" + f_name + "'.";
                        return NULL;
                    }
                    arg_names.insert(arg->to_string());
                }
                s_expression* body = (*s)[3];
                // no check for body
                // define function
                symbols.define(f_name, args, body);
                // print name of function
                r = new s_expression(token(ATOM, f_name));

            } else {                          // USER-DEFINED FUNCTION CALL //
                int num_of_args = s->size()-1;
                r = symbols.retrieve(exp, num_of_args);
                if (r == NULL) {
                    err_msg = exp + ": Function '" + exp + "' with " + itos(num_of_args) + " arguments not defined.";
                    return NULL;
                }
                s_expression *args = r->car();
                s_expression *body = r->cdr();
                // set the variables in a new scope
                symbols.push();
                s_expression **arg = new s_expression*[args->size()];
                for (int i=0; i<args->size(); i++) {
                    arg[i] = eval((*s)[i+1]);
                    if (arg[i] == NULL) {
                        // error
                        return NULL;
                    }
                }
                for (int i=0; i<args->size(); i++) {
                    string arg_name = (*args)[i]->to_string();
                    symbols.set(arg_name, arg[i]);
                }
                // evaluate and return to previous scope
                r = eval(body);
                if (r == NULL) {
                    // error
                    return NULL;
                }
                symbols.pop();

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
    string keys[] = {"T", "NIL", "CAR",  "CDR", "CONS",
                  "ATOM", "EQ",  "NULL", "INT", "PLUS",
          "QUOTIENT", "REMIANDER", "LESS", "GREATER", "COND",
                "QUOTE", "DEFUN"};
    keywords = new set<string>(keys, keys+17);
}

interpreter::~interpreter() {
    delete err_tkn;
}

bool interpreter::exec() {
    bool redirected = !isatty(fileno(stdin));
    while (true) {
        // print a prompt if input is not being redirected
        if (!redirected) {
            // cerr so output won't get redirected
            cerr << ">> ";
        }
        token t = ins.get();
        if (t.type == F_END) {
            // valid end of file
            if (!redirected) cerr << endl << "Bye." << endl;
            return true;
        }
        // not EOF, get expression
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

