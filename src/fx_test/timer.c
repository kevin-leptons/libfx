#include <fx_test/timer.h>

#include <stdlib.h>
#include <fx_error/error.h>

static void timeval_add_(struct timeval *dest, const struct timeval *src) {
        dest->tv_sec += src->tv_sec;
        dest->tv_usec += src->tv_usec;
        if (dest->tv_usec >= MICRO_INVERSE) {
                dest->tv_sec += 1;
                dest->tv_usec -= MICRO_INVERSE;
        }
}

static void timeval_sub_(struct timeval *dest, const struct timeval *src) {
        dest->tv_sec -= src->tv_sec;
        dest->tv_usec -= src->tv_usec;
        if (dest->tv_usec < 0) {
                dest->tv_sec -= 1;
                dest->tv_usec += MICRO_INVERSE;
        }
}

static void timeval_elapse_(const struct timeval *start, struct timeval *tk) {
        if (gettimeofday(tk, NULL)) {
                fx_error_kraise(errno);
                return;
        }
        timeval_sub_(tk, start);
}

void fx_test_timer_start(struct fx_test_timer *t) {
        if (gettimeofday(&t->start_point, NULL)) {
                fx_error_kraise(errno);
                return;
        }
        t->tick.tv_sec = 0;
        t->tick.tv_usec = 0;
}

void fx_test_timer_pause(struct fx_test_timer *t) {
        struct timeval tick;

        timeval_elapse_(&t->start_point, &tick);
        if (fx_error_check())
                return;
        timeval_add_(&t->tick, &tick);
}

void fx_test_timer_resume(struct fx_test_timer *t) {
        if (gettimeofday(&t->start_point, NULL)) {
                fx_error_kraise(errno);
                return;
        }
}

void fx_test_timer_stop(struct fx_test_timer *t) {
        fx_test_timer_pause(t);
}

void fx_test_timer_tick(struct fx_test_timer *t, struct timeval *v) {
        *v = t->tick;
}

double fx_test_timeval_to_double(const struct timeval *t) {
        return t->tv_sec + (double) t->tv_usec / MICRO_INVERSE;
}
