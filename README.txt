//
// CSE 755 Lisp Interpreter
//
//   Author: Andrew Groot
//

Building and Running
--------------------
    This project can be successfully build with 'gmake' and executed with './lisp < infile > outfile'.

Design Description
------------------
    This intepreter uses an object-oriented recursive descent structure.  The 'interpereter' class
receives a 'tokenizer' in its constructor and uses that to build 's_expression' objects.  The 
s_expression object is essentially a tree, with lisp-list structure as defined in class.  For
example, (1 2) or (1 . (2 . NIL)) will be store internally as the following binary tree:

               .
              / \
             1   .
                / \
               2  NIL

where 1 and 2 can be similar binary trees as well.  All data, including code, is represented as an 
s_expression and the output is also printed as s_expressions.

    The interpreter class also contains a 'symbol_table' object which defines the scope and bindings
of identifier's values.  It works like a stack, with the most recent scope on top, and allowing the
re-binding of values to an identifier in a higher scope.  The most recent valid binding is what is
used when looking up the value of an identifier.  That is to say, if x is bound to the value '3' at
the bottom of the stack and through a function call it's value is changed to '2', inside the function 
'2' will be returned.  But once the function exits, '3' is again the value of x.

    Finally, the interpreter class has a function_table which serves as an accessor for function
parameter names and bodies.  Since functions can only be declared in the outer-most scope, this 
setup forces their global visibility and provides simple storage and retrieval of the functions
specifics.

  [need more, probably just another paragraph]

