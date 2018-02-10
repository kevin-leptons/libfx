#ifndef FX_QUEUE_H
#define FX_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct fx_queue {
        size_t cap;
        void *slots;
};
typedef struct fx_queue fx_queue_t;

void fx_queue_init(fx_queue_t *q, size_t cap);
void fx_queue_free(fx_queue_t *q);
void fx_queue_recap(fx_queue_t *q, size_t cap);
void fx_queue_push(fx_queue_t  *q, void *item);
void fx_queue_front(fx_queue_t *q, void **item);
void fx_queue_pop(fx_queue_t *q, void **item);

#endif

/*
ERROR
=====
        FX_ENOMEM Not enough memory to perform operation ini() or recap()
        FX_EINDEX Not items to perform push(), front() or pop()
SIGNAL
======
        SIGABRT on error and error set to correspond error.
        SIGSEGV on pass wrong fx_queue_t pointer to functions.
*/
