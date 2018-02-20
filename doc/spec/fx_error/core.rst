[+] fx_error_core
=================

NAME
----

fx_error_core - mechanism for error handling for libfx 

SYNOPSIS
--------

.. code-block:: c

        #include <fx_error/error.h>
        // in libfx_error

        #define FX_ERROR_DCL(error_id)
        // declare error identity in header file

        #define FX_ERROR_DEF(error_id)
        // define error identity in source file

        #define FX_ERROR_ASSERT(expression)
        // verify at debug mode

        void fx_error_raise(const fx_error_t *e);
        // set fx_error_state to e 

        int fx_error_catch(const fx_error_t *e);
        // check specific error has occurs

        int fx_error_check(void);
        // check error has occurs or not

        void fx_error_clear(void);
        // set fx_error_state to FX_ENONE

        const char *fx_error_id(const fx_error_t *e);
        // get short string which describe error

DESCRIBE
--------

Specify rules to handling errors efficiency in C language, also provide APIs
to do that. Everything in libfx, used libfx should follow that rules to make
uniform error handling, together. There are rules:

**Comfort with C standard library**. That library is specifics in `ISO-IEC
9898 <http://www.open-std.org/jtc1/sc22/wg14/www/standards>`_, means
``libfx_error`` requires hosted environment to runs and does not guarantees
working on freestanding environment.

**Minimize number of error definitions**. It means define general errors and
do not define new errors with same meaning. This rules make less definitions
then less time spent to research and more less time to use.

**Minimize error definition size**. Number of errors are causes by hardware
resources is finite, however logic errors is infinite, it appears when you
create new things. If storage is not minimizes, it will be big problem. Do it
with ``FX_ERROR_DCL`` and ``FX_ERROR_DCL``.

**Diagnostic developer's mistakes at debug mode**. Errors which causes by
developers must be fix at debug mode instead of give it to other developers
at release mode. If that errors occurs, show essential information to help
find, fix bugs then abort process. At release mode, diagnostic must be
disapear to guarantee execution speed. Do it with ``FX_ERROR_ASSERT()``.

**Emit non developer's errors to caller**. That errors may be failer in
hardware resources allocating, I/0 operations or invalid data processing which
can not be fix at debug mode. This rule gives caller two choices: handle it or
emit to upper caller. Do it with ``fx_error_raise()``.

**A error state for a thread**. This rule guarantees that errors occurs in a
thread is not affect to other threads. To do that, each threads have a error
state called ``fx_error_state``.

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

        // target: raise error then abort process

        // in <yourlib/do_work_abort.h>
        void do_work_abort();           // describe why YOURLIB_E001 will
                                        // be occurs and process will be
                                        // terminate also

        // in <yourlib/do_work_abort.c>
        void do_work_abort(int arg) {
                if (...)                                // error condition
                        fx_error_abort(YOURLIB_E001);   // raise error then
                                                        // abort
        }

        // in <somewhere/do_other_work.c>
        #include <yourlib/do_work.h>    // use your APIs

        void do_other_work(void) {
                do_work_abort();        // call API
                                        // if error occurs, error state will 
                                        // be set then terminate process with
                                        // SIGABRT
        }

EXAMPLE 04
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

