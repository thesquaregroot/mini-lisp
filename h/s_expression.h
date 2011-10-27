#ifndef S_EXPRESSION_H
#define S_EXPRESSION_H 1

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
};

#endif
