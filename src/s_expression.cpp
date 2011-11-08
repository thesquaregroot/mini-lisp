
#include <cstdlib>
#include "../h/s_expression.h"
using namespace std;

// var_type type;
// std::string lex_val;
// int value;
// s_expression* lst;
// s_expression* rst;

///  constructors
s_expression::s_expression() {
    lst = NULL;
    rst = NULL;
}

s_expression::s_expression(token t) {
    lst = new s_expression();
    lst->set(t);
    rst = NULL;
}

s_expression::s_expression(token t, s_expression* list) {
    lst = new s_expression(t);
    rst = list;
}
///  destructor
s_expression::~s_expression() {
    delete lst;
    delete rst;
}

// methods
s_expression* s_expression::left() {
    return lst;
}

s_expression* s_expression::right() {
    return rst;
}

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

bool s_expression::is_leaf() {
    return (lst == NULL && rst == NULL);
}

s_expression* s_expression::operator[](int i) {
    if (i == 0) {
        return lst;
    } else {
        return (*rst)[i-1];
    }
}

int s_expression::size() {
    if (rst == NULL) {
        if (lst == NULL) {
            return 0;
        }
        return 1;
    } else {
        return (1 + rst->size());
    }
}

void s_expression::print() {
    if (lst == NULL && rst == NULL) {
        if (var_type == BOOL) {
            cout << value?"T":"NIL";
        } else {
            // INT
            cout << value;
        }
        cout << value;
    } else {
        cout << '(';
        lst->print();
        if (rst != NULL) {
            cout << ' ';
            rst->print();
        }
        cout << ')';
    }
}

