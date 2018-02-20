[+] fx_test
===========

SYNOPSIS
--------

.. code-block:: c

        
        #include <fx_test/test.h>

        void fx_test_init(fx_test_t *t, enum fx_test_mode mode);
        // initialize testing

        void fx_test_free(fx_test_t *t);
        // release resources which uses by testing

        void fx_test_run(fx_test_t *t, const fx_test_unit_set_t *s);
        // run unit tests in parallel

        void fx_test_join(fx_test_t *t, fx_test_result_t *r);
        // wait for all of unit tests finished

        void fx_test_result_dump(FILE *out, fx_test_result_t *r);
        // print testing's result
