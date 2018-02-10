
[+] fx_error_core
=================

NAME
----

fx_error_core - fx error handling mechanism

SYNOPSIS
--------

.. code-block:: c

        #include <fx_error/error.h>

        #define FX_ERROR_DCL(error_id)
        #define FX_ERROR_DEF(error_id)

        typedef struct {} fx_error_t;
        extern FX_ERROR_STATE_ATTR const fx_error_t *fx_error_state;

        void fx_error_raise(const fx_error_t *e);
        bool fx_error_catch(const fx_error_t *e);
        bool fx_error_check(void);
        void fx_error_clear(void);
        const char *fx_error_id(const fx_error_t *e);

DESCRIBE
--------

This APIs is an implementation of :ref:`fx-error-concept` called ``fx_error``.
``fx_error`` use for all of parts of ``libfx``. New code aim to part of
``libfx`` must be ``fx_error`` compliant. Code depends on ``libfx`` should be
``fx_error`` compliant to handle errors unified. This implementation also
specify three more rules for compative with C language:

**Comfort with C standard library**. That library is specifics in `ISO-IEC
9898 <http://www.open-std.org/jtc1/sc22/wg14/www/standards>`_, means APIs
requires hosted environment to runs and does not guarantees working on
freestanding environment.

**Minimize error definition size**. Number of errors are causes by hardware
resources is finite, however invalid data errors is infinite, it appears when
you create new data types. If error definition size is not minimizes, it will
be big problem.

**A error state for a thread**. This rule guarantees that errors occurs in a
thread is not affect to other threads. 

EXAMPLE 01
----------

.. code-block:: c

        // target: declare, define errors

        // in <yourlib/error.h>
        #include <fx_error/error.h>     // use fx_error APIs

        FX_ERROR_DCL(YOURLIB_E001);     // declare errors which may be occurs
        FX_ERROR_DCL(YOURLIB_E002);     // in your library
        FX_ERROR_DCL(YOURLIB_E003);

        // in <yourlib/error.c>         // define errors
        FX_ERROR_DEF(YOURLIB_E001);
        FX_ERROR_DEF(YOURLIB_E002);
        FX_ERROR_DEF(YOURLIB_E003);

        // in <yourlib/api.h> or <yourlib/api.c>
        // you can use YOURLIB_E001 with fx_error APIs

EXAMPLE 02
----------

.. code-block:: c

        // target: raise, check, handle error

        # include <yourlib/error.h>     // use your defined errors

        // in <yourlib/do_work.h>
        void do_work(void);             // describe why YOURLIB_E001 will
                                        // occurs to help other people who
                                        // uses your APIs check errors

        // in <yourlib/do_work.c>
        void do_work(void) {
                if (...) {                              // error condition
                        fx_error_raise(YOURLIB_E001);   // raise error
                        return;                         // stop function
                }
        }

        // in <somewhere/do_other_work.c>
        #include <yourlib/do_work.h>            // use your APIs

        void do_other_work(void) {
                do_work();                      // call your API
                if (fx_error_check()) {         // check error 
                                                // handle error
                }
        }

EXAMPLE 03
----------

.. code-block:: c

        // target: check, handle multi error cases

        // in <yourlib/do_work.h>
        void do_work(void);     // describe why YOURLIB_E001, YOURLIB_E002
                                // and YOURLIB_E003 will be occurs

        // in <yourlib/do_work.c>
        void do_work(void) {
                if (...) {                              // error condition 1
                        fx_error_raise(YOURLIB_E001);   // raise error
                        return;                         // stop function
                }
                if (...) {                              // the same above
                        fx_error_raise(YOURLIB_E002);
                        return;
                }
                if (...) {                              // the same above
                        fx_error_raise(YOURLIB_E003);
                        return;
                }
        }

        // in <somewhere/do_other_work.c>
        #include <yourlib/do_work.h>            // use your APIs

        void do_other_work(void) {
                do_work();                              // call API
                if (fx_error_catch(YOURLIB_E001)) {     // check and handle
                                                        // for YOURLIB_E001
                }
                if (fx_error_catch(YOURLIB_E002)) {     // check and handle
                                                        // for YOURLIB_E002
                }
                if (fx_error_catch(YOURLIB_E003)) {     // check and handle
                                                        // for YOURLIB_E003
                }
        }
