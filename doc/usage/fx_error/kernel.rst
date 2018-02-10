[+] fx_error_kernel
===================

SYNOPSIS
--------

.. code-block:: c

        #include <fx_error/kernel.h>

        const struct fx_error *fx_error_from_kernel(int code);
        // return fx_error_t * from kernel error code

        void fx_error_kraise(int code);
        // raise fx_error from kernel error code

        // pre-defined errors corespond with kernel error codes
        // for example: EPERM corespond with FX_EPERM
