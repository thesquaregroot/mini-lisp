Andrew Groot

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

  [need more]

