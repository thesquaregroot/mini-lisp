#ifndef S_EXPRESSION_H
#define S_EXPRESSION_H 1

#include "symbol_table.h"
#include "function_table.h"
#include "var_types.h"
#include "token.h"

class s_expression {
  private:
    var_type type;
    int value;
    s_expression* left;
    s_expression* right;

  public:
    // If this s_expression is not an leaf, returns a reference to the right sub-tree.
    //  If it is an leaf, returns NULL.
    //  Essentially a 'car' function.
    s_expression& left();
    // Same as 'left()' but for the right sub-tree.
    //  Essentially a 'cdr' function. 
    s_expression& right();
    // Makes this s_expression a leaf by giving it a value.
    void set(token);
    // Return true if and only if this s_expression is an leaf.
    bool is_leaf();
    // Returns the element of the list with the given index.
    //   Requires that the s_expression is a list.
    s_expression& operator[](int);
    // Print an appropriate representation of this s_expression.
    void print();
    // Return the value of this s_expression given a symbol_table and function_table.
    s_expression& value(symbol_table, function_table);
};

#endif
