#include <fx_test/test.h>

#include <stdio.h>
#include <fx_test/timer.h>

static void unit_result_dump_(const fx_error_t *error,
                              const fx_test_unit_t *unit,
                              const struct timeval *tick) {
        const char *title;
        const char *errstr;

        errstr = "";
        if (error == FX_ENONE) {
                title = "*";
        } else if (error == FX_TEST_EEXPECT) {
                title = "F";
        } else {
                title = "E";
                errstr = fx_error_id(error);
        }
        printf("[%s] %.5f %s %s\n", title, fx_test_timeval_to_double(tick),
               unit->name, errstr);
}

static void unit_run_(void *arg) {
        fx_test_unit_t *unit = arg;
        fx_test_timer_t timer;
        struct timeval tick;
        const fx_error_t *error;
        
        fx_error_clear();
        fx_test_timer_start(&timer);
        if (fx_error_check())
                return;
        unit->entry();
        error = fx_error_state;
        fx_error_clear();
        fx_test_timer_stop(&timer);
        if (fx_error_check())
                return;
        fx_test_timer_tick(&timer, &tick);
        unit_result_dump_(error, unit, &tick);
        if (fx_error_check())
                return;
        fx_error_raise(error);
}

void fx_test_init(fx_test_t *t, enum fx_test_mode mode) {
        t->mode = mode;
        fx_test_pipe_init(&t->pipe);
        fx_test_timer_start(&t->timer);
}

void fx_test_free(fx_test_t *t) {
        fx_test_pipe_free(&t->pipe);
}

void fx_test_run(fx_test_t *t, const fx_test_unit_set_t *s) {
        for (size_t i = 0; i < s->size; ++i) {
               fx_test_pipe_push(&t->pipe, unit_run_, s->items + i);
               if (fx_error_check())
                       return;
        }
}

void fx_test_join(fx_test_t *t, fx_test_result_t *r) {
        struct fx_test_pipe_result pipe_result;

        r->is_done = false;
        fx_test_pipe_join(&t->pipe, &pipe_result);
        if (fx_error_check())
                return;
        r->is_done = pipe_result.is_success;
        fx_test_timer_stop(&t->timer);
        fx_test_timer_tick(&t->timer, &r->tick);
}

void fx_test_result_dump(FILE *out, fx_test_result_t *r) {
        const char *title;

        title = r->is_done ? "SUCCESS" : "FAIL";
        fprintf(out, "%s %f\n", title, fx_test_timeval_to_double(&r->tick));
}
