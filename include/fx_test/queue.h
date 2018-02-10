#ifndef FX_TEST_QUEUE_H
#define FX_TEST_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct fx_test_queue {
        size_t size;
        size_t cap;
        void **slots;
        void **front;
        void **back;
};
typedef struct fx_test_queue fx_test_queue_t;

void fx_test_queue_init(fx_test_queue_t *q, size_t cap);
void fx_test_queue_free(fx_test_queue_t *q);
void fx_test_queue_push(fx_test_queue_t *q, void *item);
void *fx_test_queue_front(fx_test_queue_t *q);
void fx_test_queue_pop(fx_test_queue_t *q);
void fx_test_queue_clear(fx_test_queue_t *q);
size_t fx_test_queue_size(fx_test_queue_t *q);
bool fx_test_queue_empty(fx_test_queue_t *q);
bool fx_test_queue_full(fx_test_queue_t *q);

#endif
