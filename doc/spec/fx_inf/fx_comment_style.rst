fx_comment_style
================

NAME
----

fx_comment_style - fx comment style

SYNOPSIS
--------

.. code-block:: text

        With header or source files description, use multi line comment in
        top of file:

                /*
                        describe here
                        more description here
                */

                void do_some_thing();
                void do_some_thing_more();

        With function description, use multi comment in bottom side:

                void do_some_thing();
                /*
                        describe about function here
                        and more here
                */

        With statement, use one line comment in right side if it fits:

                do_some_thing();        // describe here
                                        // more description here

        With statement, use one line comment in top side if right side does
        not fit:

                // describe here
                do_some_thing_long_and_long_and_so_long();

        Do not abuse comments.

        Keep comments to be simple.

        Do not add global information to header or source files comment.

DESCRIPTION
-----------

Do not abuse comments. Source code itself can explain what is it do, almost
but not always. Then comment helps to explain some things too hard to get from
source code. If comments become too much, it is terrible to read duplicate
contents.

Keep comments to be simple. Comments helps something becomes more simple to
understand, not more complicate. So keep it short, clear, non duplicate
content.

Do not add global information to header or source files comment. That
information can be change any time then you must update all of files which
related. Other hand, you can put that information to one file, it is more
easy to find, read and update. For example: lincenses, copyright.

EXAMPLE 01
----------

.. code-block:: c

        // target: comment for header files

        /*
                fx_array: array's interface - an abstract data type.

                fx_array_t store information about array.
                fx_array_init() initialize an array
                fx_array_free() release resources which uses by array
                fx_array_set() set a value into array at specific index
                fx_array_get() get a value from array at specific index 
        */

        typedef struct {} fx_array_t;

        void fx_array_init(fx_array_t *a);
        void fx_array_free(fx_array_t *a);
        void fx_array_set(fx_array_t *a, size_t index, void *item);
        void *fx_array_get(fx_array_t *a, size_t index);

EXAMPLE 02
----------

.. code-block:: c

        // target: comment on one line in right side

        const unsigned double g = 9.8;          // gravity constant 
        const unsigned double l = 299792458;    // speed of light

EXAMPLE 03
----------

.. code-block:: c

        // target: comment for functions

        struct qe2_result {
                bool has_roots;
                double x1;
                double x2;
        };

        void solve_qe2(double a, double b, double c, struct qe2_result *r);
        /*
                Solve quadratic equation 2: y = a*x^2 + b*x + c. 
                
                If a is zero, undefined behiviors.  If equation has root,
                r->has_roots is set to true and x1, x2 is set to corresponding
                values. If not, r->has_roots is set to false and x1, x2 is not
                change.
        */
