fx_loop_style
=============

NAME
----

fx_loop_style - fx loop style

SYNOPSIS
--------

.. code-block:: text

        Use for() for all of loop.

DESCRIPTION
-----------

Use ``for()`` for all of loop.  C language provides three loop statements:
``for()``, ``while-do`` and ``do-while``, people are fucking crazy to research
it, use it and read it. Use only ``for()`` statement is unified to stop care
about other loop statements.

EXAMPLE 01
----------

.. code-block:: c

        // target: finite loop

        int array[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (size_t i = 0; i < 8; ++i) {

        }

EXAMPLE 02
----------

.. code-block:: c

        // target: infinite loop

        for (;;) {

        }

EXAMPLE 03
----------

.. code-block:: c

        // target: do some things first then check loop condition

        
        for (bool still_loop = true;;) {        // verify loop condition here

                                                // do some things to change
                                                // loop condition here

                if (!still_loop)                // check loop condition here

                        break;
        }

EXAMPLE 04
----------

.. code-block:: c

        // target: change loop condition in other statements

        
        for (bool still_loop = true; still_loop;) {     // verify loop 
                                                        // condition here

                                                        // change loop 
                                                        // condition here
        }
