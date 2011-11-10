
#include <iostream>
#include <cstdlib>
#include "../h/itos.h"
#include "../h/s_expression.h"
using namespace std;

// var_type type;
// std::string lex_val;
// int value;
// s_expression* left;
// s_expression* right;

// private
void s_expression::set(token t) {
    lex_val = t.lex_val;
    if (t.lex_val == "T") {
        type = BOOL;
        value = 1;
    } else if (t.lex_val == "NIL") {
        type = BOOL;
        value = 0;
    } else if (t.lex_val == "0" || atoi(t.lex_val.c_str()) != 0) {
        type = INT;
        value = atoi(t.lex_val.c_str());
    } else {
        type = CALL;
        lex_val = t.lex_val;
    }
}

// public
s_expression::s_expression() {
    left = NULL;
    right = NULL;
}

/***
// create an s_expression with the following structure:
//       .
//      / \
//   token NIL
*/
s_expression::s_expression(token t) {
    this->set(t);
}

/***
// create an s_expression with the following structure:
//       .
//      / \
//  token list
*/
s_expression::s_expression(token t, s_expression* list) {
    left = new s_expression();
    left->set(t);
    right = list;
}

/***
//  Append a list to another to form the following structure:
//       l           .        l        .
//        \    or   / \   or   \  or  / \
//         r       l   r        .    l   .
//                             /        /
//                            r        r
*/
s_expression::s_expression(s_expression* l, s_expression* r) {
    // Create left side
    if (l->left == NULL) {
        // single element, make list element
        left = new s_expression();
        // copy data
        left->type = l->type;
        left->value = l->value;
        left->lex_val = l->lex_val;

    } else {
        // list, use same first element
        left = l->left;
    }
    // copy the rest of l (either NULL or the rest of a list)
    right = l->right;

    // find the end of the list
    if (right == NULL) {
        // make r the last element(s)
        if (r->left == NULL) {
            // single element
            right = new s_expression();
            right->left = r;

        } else {
            // list
            right = r;
        }
    } else {
        s_expression* s = right;
        while (s->right != NULL) {
            s = s->right;
        }
        // make r the last element(s)
        if (r->left == NULL) {
            // single element
            s->right = new s_expression();
            s->right->left = r;

        } else {
            // list
            s->right = r;
        }
    }
}

///  destructor
s_expression::~s_expression() {
    delete left;
    delete right;
}

// methods
s_expression* s_expression::car() {
    return left;
}

s_expression* s_expression::cdr() {
    return right;
}

s_expression* s_expression::operator[](int i) {
    if (i == 0) {
        return left;
    } else {
        return (*right)[i-1];
    }
}

bool s_expression::is_leaf() {
    return (left == NULL);
}

int s_expression::size() {
    if (right == NULL) {
        if (left == NULL) {
            return 0;
        }
        return 1;
    } else {
        return (1 + right->size());
    }
}

string s_expression::to_string() {
    string str;
    if (left == NULL) {
        if (type == BOOL) {
            str = (value>0)?"T":"NIL";
        } else {
            // INT
            if (lex_val != "") {
                str = lex_val;
            } else {
                str = itos(value);
            }
        }
    } else {
        str = '(';
        str += left->to_string();
        if (right != NULL && right->left != NULL) {
            str += " . ";
            /*     .
            //    / \
            //   .   . <- right
            //      /
            //    (.)  <- going here (right->left)
            */
            str += right->left->to_string();
        }
        str += ')';
    }
    return str;
}

