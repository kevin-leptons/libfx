fx_page_style
=============

NAME
----

fx_page_style - fx page style

SYNOPSIS
--------

.. code-block:: c

        Maximum characters per line is 78.

        Indentation is 8 spaces.

DESCRIPTION
-----------

Maximum characters per line is 78. First, it is historical. Terminal devices
can display 80 characters per line, if you need text work well on that
devices, you must limit at 78 characters after you spend one character for
enter line and one character for indentation with right edge screen. Second,
it is printable. With 78 characters per line, it is able to print to A4 paper
which popular paper size. Third, reader no need to scroll screen to see what
is happens out of 80 characters wide.

Indentation is 8 spaces. First, it helps reader to distinguish indentation
clearly and warns about too much nested blocks. Second, it helps printing to
A4 paper correctly, not affected by custom tab size.

EXAMPLE 01
----------

.. code-block:: text

        // target: indentation by 8 spaces

        ****************************************
                ******************************** 
                ******************************** 
                ******************************** 
                ******************************** 
        <------> 8 space

        ****************************************
        ****************************************
        ****************************************
        ****************************************
                ******************************** 
                ******************************** 
        <------> 8 space

REFERENCES
----------

`Character per line - Wikipedia
<https://en.wikipedia.org/wiki/Characters_per_line>`_
