#ifndef S_EXPRESSION_H
#define S_EXPRESSION_H 1

#include <string>
#include "var_type.h"
#include "token.h"

class s_expression {
  private:
    var_type v_type;
    std::string lex_val;
    int val;
    s_expression* left;
    s_expression* right;
    
    // Makes this s_expression a leaf by giving it a value.
    void set(token);
    // Does the work for operator[].
    s_expression* access(int) const;
    // Does the work for is_list.
    bool list() const;
    // Does the work for size.
    int length() const;

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

    // Returns a pointer reference to the left sub-tree. 
    s_expression*& car();
    // Returns a pointer reference to the right sub-tree. 
    s_expression*& cdr();
    // returns true iff the tree is a list.
    bool is_list() const;
    // returns true iff the tree is a node.
    bool is_leaf() const;
    // returns true iff the tree is a leaf and has value 'NIL'.
    bool is_null() const;
    // returns the type of a leaf node
    var_type type() const;
    // returns the value of a leaf node
    int value() const;
    // Returns the element of the list with the given index.
    //   Requires that the s_expression is a list.
    s_expression* operator[](int);
    // Returns the number of element of the list (requires a list).
    //   i.e.:
    //       (1 2 3)
    //       (1 2 (3 4))
    //       ((1) (2 3) (4))
    //                      all have size = 3.
    int size() const;
    // Returns an appropriate string representation of this s_expression.
    std::string to_string() const;
    // Returns true iff both s-expressions are leafs and have equal types and values.
    bool operator==(const s_expression) const;
};

#endif
