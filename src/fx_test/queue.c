#include <fx_test/queue.h>

#include <fx_error/error.h>

void fx_test_queue_init(fx_test_queue_t *q, size_t cap) {
        void **slots;

        slots = malloc(sizeof(*slots) * cap);
        if (!slots) {
                fx_error_kraise(errno);
                return;
        }

        q->cap = cap;
        q->size = 0;
        q->slots = slots;
        q->front = q->slots + cap - 1;
        q->back = q->front;
}

void fx_test_queue_free(fx_test_queue_t *q) {
        free(q->slots);
}

void fx_test_queue_push(fx_test_queue_t *q, void *item) {
        *q->back = item;
        q->size++;
        if (q->back == q->slots)
                q->back = q->slots + q->cap - 1;
        else
                q->back--;
}

void *fx_test_queue_front(fx_test_queue_t *q) {
        return *q->front;
}

void fx_test_queue_pop(fx_test_queue_t *q) {
        if (q->front == q->slots)
                q->front = q->slots + q->cap - 1;
        else
                q->front--;
        q->size--;
}

void fx_test_queue_clear(fx_test_queue_t *q) {
        q->size = 0;
        q->front = q->slots + q->cap - 1;
        q->back = q->front;
}

size_t fx_test_queue_size(fx_test_queue_t *q) {
        return q->size;
}

bool fx_test_queue_empty(fx_test_queue_t *q) {
        return q->size == 0;
}

bool fx_test_queue_full(fx_test_queue_t *q) {
        return q->size == q->cap;
}
