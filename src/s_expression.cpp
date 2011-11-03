
#include <cstdlib>
#include "../h/s_expression.h"
using namespace std;

// var_type type;
// int value;
// s_expression* left;
// s_expression* right;

s_expression& s_expression::left() {
    return left;
}

s_expression& s_expression::right() {
    return right;
}

void s_expression::set(token t) {
    if (t.lexval == "T") {
        type = BOOL;
        value = 1;
    } else if (t.lexval == "NIL") {
        type = BOOL;
        value = 0;
    } else {
        type = INT;
        value = atoi(t.lexval.c_str());
    }
}

bool s_expression::is_leaf() {
    return (left == NULL && right == NULL);
}

s_expression& s_expression::operator[](int i) {
    if (i == 0) {
        return left;
    } else {
        return (*right)[i-1];
    }
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

void s_expression::print() {
    if (left == NULL && right == NULL) {
        if (var_type == BOOL) {
            cout << value?"T":"NIL";
        } else {
            cout << value;
        }
        cout << value;
    } else {
        cout << '(';
        left->print();
        if (right == NULL) {
            cout << ' ';
            right->print();
        }
        cout << ')';
    }
}

s_expression& value(symbol_table, function_table) {
    
}

