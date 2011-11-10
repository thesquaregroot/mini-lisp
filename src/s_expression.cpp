
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

// create a leaf node
s_expression::s_expression(token t) {
    left = NULL;
    right = NULL;
    this->set(t);
}

/***
// Create a list from two s_expressions in the following structure:
//
//    .
//   / \
//  l   .
//     /
//    r
*/
s_expression::s_expression(s_expression* l, s_expression* r) {
    left = l;
    // single element
    right = new s_expression();
    right->left = r;
}

///  destructor
s_expression::~s_expression() {
    delete left;
    delete right;
}

// methods
s_expression*& s_expression::car() {
    return left;
}

s_expression*& s_expression::cdr() {
    return right;
}

/***
// Create the following structure:
//
//  this
//    \
//     r
*/
s_expression* s_expression::append_right(s_expression* r) {
    s_expression* s = this;
    while (s->right != NULL) {
        s = s->right;
    }
    s->right = r;
    return this;
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
        if (right != NULL) {
            str += " . ";
            /*     .
            //    / \
            //   .   . <- right
            //      /
            //    (.)  <- going here (right->left)
            */
            str += right->to_string();
        }
        str += ')';
    }
    return str;
}

