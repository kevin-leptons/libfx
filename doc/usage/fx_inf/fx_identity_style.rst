fx_identity_style
=================

NAME
----

fx_identity_style - fx identity style

SYNOPSIS
--------

.. code-block:: text

        [A-Z][A-Z0-9_]+                 // macros
        [a-z][a-z0-9_]+                 // every things is not macros:
                                        // constants, variables, functions
                                        // structure, enum, union

        Keep identity name as short as possible but still not too hard to
        understand.

DESCRIPTION
-----------

Macro must be all upper case characters. Because macro's behaviors are
different than C code, it is important to distinguish macro and C code.

Other things are not macro must be lower case characters. Lower cases are
more quick to write and more easy to read than lower interleave upper case
characters.

Keep identity name as short as possible but still not too hard to understand.
This style does not specify minimum or maximum lenght of identity name because
that is unreasonable, sometime long names are not avoidable, sometime short
names are efficiency. Long names may be easy to understand but it cause too
long lines and take long time to read. Short name enough is harmonious between
understandable and readable.

EXAMPLE 01
----------

.. code-block:: c

        // target: valid macro's name

        #define FX_ERROR_H
        #define FX_YES 1
        #define FX_NO 0
        #define FX_COE 0x1234567A

EXAMPLE 02
----------

.. code-block:: c

        // target: invalid macro's name

        #define fx_error_h              // not upper case
        #define FX_ERROR_h              // not upper case completly
        #define _FX_ERROR_H             // _ prefix are reserved names
        #define __FX_ERROR_H            // __ prefix are reserved names

EXAMPLE 03
----------

.. code-block:: c

        // target: valid identity names

        unsigned int year;
        unsigned char month;
        unsigned char day_in_month;
        unsigned char day_in_week;
        const double pi = 3.14;

        struct date {};
        void now_date(struct date *d);

EXAMPLE 04
----------

.. code-block:: c
        
        // target: invalid identity names

        unsigned int _year;             // _ prefix are reserved names
        unsigned int __year;            // __ prefix are reserved names

        unsigned int Year;              // contain upper case
        struct Date {};
        void Now_date(struct Date *d);
        const double PI = 3.14;

EXAMPLE 05
----------

.. code-block:: c

        // target: wrong identity names - too long

        const double gravity_constant = 9.8;    // g is enough
                                                // any one work with physical
                                                // theory know what is g
                                                // if not, they should
                                                // research to know

        struct input_output_type {};            // io_type is engouh
                                                // any one know what is io

        // too long name: interator, i is engough
        for (size_t interator = 0; interator < 8; ++interator) {}

EXAMPLE 06
----------

.. code-block:: c

        // target: wrong identity names - too short

        double s(double x) {                    // too short to understand
                return x * x;
        }

        double a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        double b[8];

        for (size_t i = 0; i < 8; ++i)          // we will look for s() to see
                b[i] = s(a[i]);                 // what is it doing because
                                                // we can not know from it
                                                // name, it is wasted time
