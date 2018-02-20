fx_hide_info_concept
====================

NAME
----

fx_hide_info_concept - fx hide information concept

SYNOPSIS
--------

.. code-block:: text

	typedef struct {} <name>_t;	// for private type        
        struct <name> {}; 		// for public type

        show interfaces                 // functions, data types
        hide implementation

DESCRIPTION
-----------

Hide information mean do not allow to access to unnecessary things. That
appears when you design function's interface and implement it, then you show
interface and hide any thing of implementation, that is hide information. 

First advantage, help programmers focuses on things which they can do. With
specifications of interface, programmers knows what is provides by interfaces
exactly, then they can learn it in right way. If any things are show,
programmers does not know where to start and follow what ways, that like a
find way in a maze.

Second advantage, prevent wrong behaviors from programmers. Programers who use
interfaces have not enough knowledge about implementation and they also do not
want to know that. If they do some things with implementation then that
behaviors may be wrong.  Do not allow programmers to work with implementation
avoid that problems.

Third advantage, keep interface is stable while implement changes freely.
Because no one touch to implementation, change it will not affect to where
uses interfaces. If you have new idea to make implementation better, just do
it and interfaces still work well.

Use ``typedef struct {} <name>_t`` to define private data types. Private data
types does not allows to access to member's fields directly, except functions
in implementation. So when you see a type name with format ``<name>_t``, do
not access to it's members. Although ``<name>_t`` is POSIX's reserved name, we
can not find any a better way to do that so we still use that format. Remember
that we always put prefix before name such as ``fx_<name>-t`` so conflict will
not happen.

Use ``struct <name> {}`` to define public data types. Public data types
allows to access to data's fields freely.

EXAMPLE 01
----------

.. code-block:: c

        // target: show interface, hide implementation and use interface

        // in <yourlib/fx_array.h>
        // show interface: data type and functions
        typedef struct {} fx_array_t;
        void fx_array_init(fx_array_t *a, size_t cap); 
        void fx_array_free(fx_array_t *a);
        void fx_array_set(fx_array_t *a, size_t index, void *item);
        void *fx_array_get(fx_array_t *a, size_t index);

        // in <yourlib/fx_array.c>
        // hide implementation, also define it
        void fx_array_init(fx_array_t *a, size_t cap) {}
        void fx_array_free(fx_array_t *a) {}
        void fx_array_set(fx_array_t *a, size_t index, void *item) {}
        void *fx_array_get(fx_array_t *a, size_t index) {}

        // in <somewhere/main.c>
        // use interface
        #include <yourlib/fx_array.h>

        fx_array_t v;
        int data = 64;
        int *item;

        fx_array_init(&a, 128);
        fx_array_set(&a, 0, &data);
        item = (int *) fx_array_get(&a, 0);

EXAMPLE 02
----------

.. code-block:: c

        // target: wrong access to private data type

        typedef struct {                // define private type
                size_t cap;
                void **slots;
        } fx_array_t;

        int item = 8;
        fx_array_t a;                   // define a instance
        a.slots[0] = (void *) &item;    // do not do this

        fx_array_set(&a, 0, &item);     // let interface do that

EXAMPLE 03
----------

.. code-block:: c

        // target: work with public data type

        // define interface: public data types and function
        struct qe2_input {
                double a;
                double b;
                double c
        };

        struct qe2_output {
                bool has_roots;
                double x1;
                double x2;
        };

        void solve_qe2(struct qe2_input &in, struct qe2_output &out) {}

        // use interface
        struct qe2_input in;
        struct qe2_output out;

        in.a = 3;                       // set members freely
        in.b = 4;
        in.c = 5;
        solve_qe2(&in, &out);

        if (out.has_roots) {            // get members freely
                out.x1;
                out.x2;
        }

        /*
                That this, public data types occurs when you need to pass
                input arguments or get output data
        */


REFERENCES
----------

`IEEE Std 1003.1-2008 POSIX - Portable Operating System Interface
<https://standards.ieee.org/findstds/standard/1003.1-2008.html>`_
