#ifndef FX_TEST_PIPE_H
#define FX_TEST_PIPE_H

#include <pthread.h>
#include <fx_test/queue.h>

struct fx_test_pipe {
        fx_test_queue_t tasks;
        pthread_cond_t tasks_full;
        pthread_cond_t tasks_not_empty;
        pthread_mutex_t tasks_mutex;
        pthread_t *workers;
        size_t num_workers;
};
typedef struct fx_test_pipe fx_test_pipe_t;

struct fx_test_pipe_result {
        bool is_success;
};

void fx_test_pipe_init(fx_test_pipe_t *p);
void fx_test_pipe_free(fx_test_pipe_t *p);
void fx_test_pipe_push(fx_test_pipe_t *p, void (*entry)(void*), void *arg);
void fx_test_pipe_join(fx_test_pipe_t *p, struct fx_test_pipe_result *r);

#endif
