
#include <iostream>
#include <cstdlib>
#include "../h/itos.h"
#include "../h/s_expression.h"
using namespace std;

// var_type v_type;
// std::string lex_val;
// int val;
// s_expression* left;
// s_expression* right;

// private
void s_expression::set(token t) {
    lex_val = t.lex_val;
    if (t.lex_val == "T") {
        v_type = BOOL;
        val = 1;
    } else if (t.lex_val == "NIL") {
        v_type = BOOL;
        val = 0;
    } else if (t.lex_val == "0" || atoi(t.lex_val.c_str()) != 0) {
        v_type = INT;
        val = atoi(t.lex_val.c_str());
    } else {
        v_type = IDENT;
        lex_val = t.lex_val;
    }
}

s_expression* s_expression::access(int i) {
    if (i == 0) {
        return left;
    } else {
        return (*right)[i-1];
    }
}

bool s_expression::list() {
    if (left != NULL && (right == NULL || (right->v_type == BOOL && right->val == 0))) {
        /* has this structure:
        //    . <- this
        //   / \
        //  .  NIL
        */
        return true;
    } else {
        /* has this structure:
        //    . <- this
        //   / \  
        //  .   .
        //     / \  
        //    .   NIL
        */
        return (right != NULL && right->list());
    }
}

int s_expression::length() {
    if (right == NULL) {
        if (left == NULL) {
            return 0;
        }
        return 1;
    } else {
        return (1 + right->size());
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

// returns true iff the tree is a leaf and has value 'NIL'
bool s_expression::is_nil() {
    return (v_type == BOOL && val == 0);
}

// returns the type of a leaf node
var_type s_expression::type() {
    return v_type;
}

// returns the value of a leaf node
int s_expression::value() {
    return val;
}

s_expression* s_expression::operator[](int i) {
    return this->access(i);
}

bool s_expression::is_leaf() {
    return (left == NULL);
}

bool s_expression::is_list() {
    return this->list();
}

int s_expression::size() {
    return this->length();
}

string s_expression::to_string() {
    string str;
    if (left == NULL) {
        if (v_type == BOOL) {
            str = (val>0)?"T":"NIL";
        } else {
            // INT
            if (lex_val != "") {
                str = lex_val;
            } else {
                str = itos(val);
            }
        }
    } else {
        if (this->list()) {
            str = '(';
            for (int i=0; i<this->length(); i++) {
                str += (*this)[i]->to_string();
                if (i+1 != this->length()) {
                    str += ' ';
                }
            }
            str += ')';
        } else { 
            str = '(';
            str += left->to_string();
            if (right != NULL && right->lex_val != "NIL") {
                str += " . ";
                str += right->to_string();
            }
            str += ')';
        }
    }
    return str;
}

