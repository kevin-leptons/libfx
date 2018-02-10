#include <test/fx.h>

#include <stdio.h>
#include <fx/vector.h>
#include <fx_error/error.h>
#include <fx_test/test.h>

#define INVALID_CAP 99999999999
#define VALID_CAP 100

void test_vector_init(void) {
        fx_vector_t v;
        fx_vector_init(&v, 0);
        fx_vector_free(&v);
}

void test_vector_recap(void) {
        fx_vector_t v;
        fx_vector_init(&v, 0);
        if (fx_error_check())
                return;
        fx_vector_recap(&v, VALID_CAP);
        if (fx_error_check()) {
                fx_vector_free(&v);
                return;
        }
        fx_vector_free(&v);
}

void test_vector_resize(void) {
        fx_vector_t v;
        fx_vector_init(&v, 0);
                return;
        fx_vector_resize(&v, VALID_CAP);
        fx_vector_free(&v);
}

void test_vector_init_fail(void) {
        fx_vector_t v;
        fx_vector_init(&v, INVALID_CAP);
        if (fx_error_catch(FX_ENOMEM)) {
                fx_error_clear();
                return;
        }
        fx_vector_free(&v);
}

void test_vector_recap_fail(void) {
        fx_vector_t v;
        fx_vector_init(&v, 0);
        if (fx_error_check())
                return;
        fx_vector_recap(&v, INVALID_CAP);
        if (fx_error_catch(FX_ENOMEM)) {
                fx_vector_free(&v);
                fx_error_clear();
                return;
        }
        fx_vector_free(&v);
}

void test_vector_resize_fail(void) {
        fx_vector_t v;
        fx_vector_init(&v, 0);
        if (fx_error_check())
                return;
        fx_vector_resize(&v, INVALID_CAP);
        if (fx_error_catch(FX_ENOMEM)) {
                fx_error_clear();
                return;
        }
        fx_vector_free(&v);
}

void test_fail(void) {
        fx_error_raise(FX_TEST_EEXPECT);
}

void test_error(void) {
        fx_error_raise(FX_ENOMEM);
}

void test_success(void) {
}

static fx_test_unit_t test_units[] = {
        FX_TEST_UNIT(test_vector_init),
        FX_TEST_UNIT(test_vector_recap),
        FX_TEST_UNIT(test_vector_resize),
        FX_TEST_UNIT(test_vector_init_fail),
        FX_TEST_UNIT(test_vector_recap_fail),
        FX_TEST_UNIT(test_vector_resize_fail),
        FX_TEST_UNIT(test_fail),
        /*FX_TEST_UNIT(test_error),*/
        FX_TEST_UNIT(test_success),
};

fx_test_unit_set_t test_vector_set = {
        .size = sizeof(test_units) / sizeof(fx_test_unit_t),
        .items = test_units
};
