#include <fx_test/pipe.h>

#include <unistd.h>
#include <fx_error/error.h>

#define PIPE_SIZE_COE 8

struct pipe_task {
        void (*entry)(void *arg);
        void *arg;
};

static struct pipe_task *pipe_task_new_(void (*entry)(void *), void *arg) {
        struct pipe_task *task;
        task = malloc(sizeof(*task));
        if (!task) {
                fx_error_kraise(errno);
                return NULL;
        }
        task->entry = entry;
        task->arg = arg;
        return task;
}

static void pipe_task_free(struct pipe_task *task) {
        free(task);
}

static void pipe_push_(fx_test_pipe_t *p, struct pipe_task *task) {
        errno = 0;

        pthread_mutex_lock(&p->tasks_mutex);
        FX_ERROR_ASSERT(!errno);
        for (; fx_test_queue_full(&p->tasks);)  {
                pthread_cond_wait(&p->tasks_full, &p->tasks_mutex);
                FX_ERROR_ASSERT(!errno);
        }

        fx_test_queue_push(&p->tasks, task);
        pthread_mutex_unlock(&p->tasks_mutex);
        FX_ERROR_ASSERT(!errno);
        pthread_cond_signal(&p->tasks_not_empty);
        FX_ERROR_ASSERT(!errno);
}

static void *thread_pool_entry_(void *arg) {
/*
        Return fx_error_t * as a last error occur in thread.
        On successfully, return FX_ENONE.
        On failure, return coresspond error.
        Do not modify returned value because it is constant.
*/
        fx_test_pipe_t *p = (fx_test_pipe_t *) arg;
        struct pipe_task *task;
        int ret;

        for (;;) {
                if (pthread_mutex_lock(&p->tasks_mutex))
                        return (void *) fx_error_from_kernel(errno);
                for (; fx_test_queue_empty(&p->tasks);) {
                        ret = pthread_cond_wait(&p->tasks_not_empty,
                                                &p->tasks_mutex);
                        if (ret)
                                return (void *) fx_error_from_kernel(errno);
                }

                task = fx_test_queue_front(&p->tasks);
                if (!task) {
                        pthread_mutex_unlock(&p->tasks_mutex);
                        pthread_cond_broadcast(&p->tasks_not_empty);
                        return (void *) FX_ENONE;
                }
                fx_test_queue_pop(&p->tasks);
                if (pthread_mutex_unlock(&p->tasks_mutex)) {
                        pthread_cond_signal(&p->tasks_full);
                        return (void *) fx_error_from_kernel(errno);
                }
                if (pthread_cond_signal(&p->tasks_full))
                        return (void *) fx_error_from_kernel(errno);

                task->entry(task->arg);
                if (fx_error_check()) {
                        pipe_task_free(task);
                        return (void *) fx_error_from_kernel(errno);
                }
                pipe_task_free(task);
        }
}

static void thread_pool_init_(fx_test_pipe_t *p, size_t pool_size) {
        int errno_tmp;

        errno = 0;
        p->workers = malloc(sizeof(pthread_t) * pool_size);
        if (!p->workers)
                return;
        p->num_workers = pool_size;

        pthread_cond_init(&p->tasks_full, NULL);
        FX_ERROR_ASSERT(!errno);
        pthread_cond_init(&p->tasks_not_empty, NULL);
        FX_ERROR_ASSERT(!errno);
        pthread_mutex_init(&p->tasks_mutex, NULL);
        FX_ERROR_ASSERT(!errno);

        for (size_t i = 0; i < pool_size; ++i) {
                pthread_create(p->workers + i, NULL, 
                                     thread_pool_entry_, (void *) p);
                if (errno) {
                        errno_tmp = errno;
                        errno = 0;
                        pipe_push_(p, NULL);
                        for (size_t k = 0; k < i; ++k) {
                                pthread_join(p->workers[i], NULL);
                                FX_ERROR_ASSERT(!errno);
                        }
                        pthread_cond_destroy(&p->tasks_full);
                        pthread_cond_destroy(&p->tasks_not_empty);
                        pthread_mutex_destroy(&p->tasks_mutex);
                        free(p->workers);
                        fx_error_kraise(errno_tmp);
                }
        }
}

static size_t sys_num_cores_() {
        return sysconf(_SC_NPROCESSORS_ONLN);
};

void fx_test_pipe_init(fx_test_pipe_t *p) {
        size_t num_cores;

        num_cores = sys_num_cores_();
        if (fx_error_check())
                return;
        fx_test_queue_init(&p->tasks, PIPE_SIZE_COE * num_cores);
        if (fx_error_check())
                return;
        thread_pool_init_(p, num_cores);
        if (fx_error_check()) {
                fx_test_queue_free(&p->tasks);
                return;
        }
}

void fx_test_pipe_free(fx_test_pipe_t *p) {
        fx_test_queue_free(&p->tasks);
        pthread_mutex_destroy(&p->tasks_mutex);
        pthread_cond_destroy(&p->tasks_full);
        pthread_cond_destroy(&p->tasks_not_empty);
}

void fx_test_pipe_push(fx_test_pipe_t *p, void (*entry)(void*), void *arg) {
        struct pipe_task *task = pipe_task_new_(entry, arg);
        pipe_push_(p, task);
}

void fx_test_pipe_join(fx_test_pipe_t *p, struct fx_test_pipe_result *r) {
        fx_error_t *worker_result;

        pipe_push_(p, NULL);
        r->is_success = true;
        for (size_t i = 0; i < p->num_workers; ++i) {
                if (pthread_join(p->workers[i], (void *) &worker_result)) {
                        fx_error_kraise(errno);
                        r->is_success = false;
                        return;
                }
                if (worker_result != FX_ENONE)
                        r->is_success = false;
        }
}
