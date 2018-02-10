#ifndef FX_TEST_TIMER_H
#define FX_TEST_TIMER_H

#include <sys/time.h>

#define MICRO_INVERSE 100000

struct fx_test_timer {
        struct timeval start_point;
        struct timeval tick;
};
typedef struct fx_test_timer fx_test_timer_t;

void fx_test_timer_start(struct fx_test_timer *t);
void fx_test_timer_pause(struct fx_test_timer *t);
void fx_test_timer_resume(struct fx_test_timer *t);
void fx_test_timer_stop(struct fx_test_timer *t);
void fx_test_timer_tick(struct fx_test_timer *t, struct timeval *v);
double fx_test_timeval_to_double(const struct timeval *t);

#endif
