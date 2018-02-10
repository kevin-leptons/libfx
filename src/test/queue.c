#include <fx_test/test.h>
#include <fx/queue.h>
#include <fx_error/error.h>
#include <signal.h>

#define INVALID_CAP 99999999999

void test_queue_init_fail(void) {
        fx_queue_t q;
        fx_queue_init(&q, INVALID_CAP);
        if (fx_error_catch(FX_ENOMEM)) {
                fx_error_clear();
                return;
        }
}

static fx_test_unit_t test_units[] = {
        FX_TEST_UNIT(test_queue_init_fail),
};

fx_test_unit_set_t test_queue_set = {
        .size = sizeof(test_units) / sizeof(fx_test_unit_t),
        .items = test_units
};
