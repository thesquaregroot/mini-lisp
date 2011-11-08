#ifndef S_EXPRESSION_H
#define S_EXPRESSION_H 1

#include <string>
#include "symbol_table.h"
#include "var_type.h"
#include "token.h"

class s_expression {
  private:
    var_type type;
    std::string lex_val;
    s_expression* lst;
    s_expression* rst;

  public:
    s_expression();
    s_expression(token);
    s_expression(token, s_expression*);
    ~s_expression();

    // If this s_expression is not an leaf, returns a reference to the right sub-tree.
    //  If it is an leaf, returns NULL.
    //  Essentially a 'car' function.
    s_expression* left();
    // Same as 'left()' but for the right sub-tree.
    //  Essentially a 'cdr' function. 
    s_expression* right();
    // Makes this s_expression a leaf by giving it a value.
    void set(token);
    // Return true if and only if this s_expression is an leaf.
    bool is_leaf();
    // Returns the element of the list with the given index.
    //   Requires that the s_expression is a list.
    s_expression* operator[](int);
    // Print an appropriate representation of this s_expression.
    void print();
};

#endif
