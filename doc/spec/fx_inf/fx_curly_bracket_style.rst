fx_curly_bracket_style
======================

NAME
----

fx_curly_bracket_style - fx curly brackets style

SYNOPSIS
--------

.. code-block:: c

        Open and close curly brackets in same line if it is fits in one line.

        Open curly brackets in same line and close curly brackets in next
        line if it is not fits on one line.

DESCRIPTION
-----------

Open and close curly brackets in same line if it is fit. It saves space.

Open curly brackets in same line and close curly brackets in next line. It
saves space and it is unified rule for open-close blocks. Maybe open block in
next line for function is more easy to read but it is conflicts with rest of
components such as ``struct``, ``enum``, so just pick one rule and it becomes
unified, mean that easy to use.

EXAMPLE 01
----------

.. code-block:: c

        // target:: open and close curly brackets on one line

        enum week_day {mon, tue, wed, thus, fri, sat, sun};

        unsigned char odd_numbers[] = {1, 3, 5, 7, 9};

EXAMPLE 02
----------

.. code-block:: c

        // target: open and close curly brackets on multi line

        struct qe2_result {
                bool has_roots;
                double x1;
                double x2;
        };

        void solve_qe2(double a, double b, double c, struct qe2_result *r) {

        }

        for (unsigned int i = 0; i < 10; ++i) {

        }
