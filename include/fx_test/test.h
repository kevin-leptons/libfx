#ifndef FX_TEST_TEST_H
#define FX_TEST_TEST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <fx_test/error.h>
#include <fx_test/timer.h>
#include <fx_test/pipe.h>

struct fx_test_unit {
        const char *name;
        void (*entry)(void);
};
typedef struct fx_test_unit fx_test_unit_t;

struct fx_test_unit_set {
        fx_test_unit_t *items;
        size_t size;
};
typedef struct fx_test_unit_set fx_test_unit_set_t;

enum fx_test_mode {fx_test_mode_force, fx_test_mode_int};

struct fx_test {
        enum fx_test_mode mode;
        fx_test_pipe_t pipe;
        fx_test_timer_t timer;
};
typedef struct fx_test fx_test_t;

struct fx_test_result {
        bool is_done;
        struct timeval tick;
};
typedef struct fx_test_result fx_test_result_t;

void fx_test_init(fx_test_t *t, enum fx_test_mode mode);
void fx_test_free(fx_test_t *t);
void fx_test_run(fx_test_t *t, const fx_test_unit_set_t *s);
void fx_test_join(fx_test_t *t, fx_test_result_t *r);
void fx_test_result_dump(FILE *out, fx_test_result_t *r);

#define FX_TEST_UNIT(entry_name) { \
        .name = #entry_name, \
        .entry = entry_name \
}

#endif
