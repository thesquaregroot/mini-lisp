#ifndef S_EXPRESSION_H
#define S_EXPRESSION_H 1

#include <string>
#include "var_type.h"
#include "token.h"

class s_expression {
  private:
    var_type type;
    std::string lex_val;
    int value;
    s_expression* left;
    s_expression* right;
    
    // Makes this s_expression a leaf by giving it a value.
    void set(token);

  public:
    ///
    // Create an empty s_expression.
    s_expression();
    // create a leaf node
    s_expression(token);
    /***
    //  create an s_expression with the following structure:
    //      .
    //     / \
    //  s_exp .
    //       /
    //     s_exp
    */
    s_expression(s_expression*, s_expression*);
    ~s_expression();

    // If this s_expression is not an leaf, returns a reference to the right sub-tree.
    //  If it is an leaf, returns NULL.
    //  Essentially a 'car' function.
    s_expression*& car();
    // Same as 'left()' but for the right sub-tree.
    //  Essentially a 'cdr' function. 
    s_expression*& cdr();
    /***
    // Create the following structure:
    //
    //  this
    //    \
    //   s_exp
    */
    s_expression* append_right(s_expression*);
    // returns true iff the tree is a node
    bool is_leaf();
    // Returns the element of the list with the given index.
    //   Requires that the s_expression is a list.
    s_expression* operator[](int);
    // Returns the number of element of the list
    //   i.e.:
    //       (1 2 3)
    //       (1 2 (3 4))
    //       ((1) (2 3) (4))
    //                      all have size = 3.
    int size();
    // Returns an appropriate string representation of this s_expression.
    std::string to_string();
};

#endif
