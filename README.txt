//
// CSE 755 Lisp Interpreter
//
//   Author: Andrew Groot
//

--------------------
Building and Running
--------------------
    This project can be successfully build with 'gmake' and executed with './lisp < infile > outfile'.

------------------
Design Description
------------------
    This intepreter uses an object-oriented recursive descent structure.  The 'interpereter' class
receives a 'tokenizer' in its constructor which it uses that to build 's_expression' objects.  The 
s_expression object is essentially a tree, with lisp-list structure as defined in class.  For
example, (1 2) or (1 . (2 . NIL)) will be stored internally as the following binary tree:

               .
              / \
             1   .
                / \
               2  NIL

where 1 and 2 can be similar binary trees, or just leafs or atoms.  All data, including code, is
represented as an s_expression and the output is also printed as s_expressions.

    The interpreter class also contains a 'symbol_table' object which defines the scope and bindings
of identifier's values.  It works like a stack, with the most recent scope on top, and allowing the
re-binding of values to an identifier in a higher scope.  The most recent valid binding is what is
used when looking up the value of an identifier.  That is to say, if x is bound to the value '3' at
the bottom of the stack and through a function call it's value is changed to '2', inside the
function '2' will be returned.  But once the function exits, '3' is again the value of x.

    The symbol_table class also serves as an accessor for function parameter lists and bodies.
Since functions can only be declared in the outer-most scope, this setup forces their global
visibility and provides simple storage and retrieval of the function's specifics.  

  [need more, probably just another paragraph]

------------
Grammar Used
------------
    The following grammar, based on the one given in the project description, represent the set of
all syntactically valid s-expressions (but not necessarily semantically valid) and is used by this
interpreter to generate s_expression objects:

    <start>  ::= <expr>

    <expr>   ::= atom
               | ( )
               | ( <expr> )
               | ( <expr> <list> )
               | ( <expr> . <expr> )

    <list>   ::= <expr>
               | <expr> <list>

    This grammar can be seen as a simplification of the grammar in the project description as it
contains fewer non-terminal symbols.  Furthermore, the structure of an s-expression, with elements
concatenated either in series by spaces or two at a time with a period, can be seen a bit more
clearly in its rules.

