#include <fx/vector.h>

#include <string.h>
#include <fx_error/error.h>

void fx_vector_init(fx_vector_t *v, size_t cap) {
        fx_vector_t new_v = {.cap = cap, .size = 0};
        new_v.slots = malloc(sizeof(void *) * cap);
        if (!new_v.slots) {
                fx_error_kraise(errno);
                return;
        }
        *v = new_v;
}

void fx_vector_free(fx_vector_t *v) {
        free(v->slots);
        v->cap = 0;
        v->size = 0;
        v->slots = NULL;
}

void fx_vector_recap(fx_vector_t *v, size_t cap) {
        fx_vector_t new_v;
        fx_vector_init(&new_v, cap);
        if (fx_error_check())
                return;
        new_v.size = v->size < cap ? v->size : cap;
        memcpy(new_v.slots, v->slots, new_v.size);

        free(v->slots);
        *v = new_v;
}

void fx_vector_resize(fx_vector_t *v, size_t size)
{
        fx_vector_t new_v;
        fx_vector_init(&new_v, size);
        if (fx_error_check())
                return;
        memcpy(new_v.slots, v->slots, size < v->size ? size : v->size);
        new_v.size = size;
        *v = new_v;
}

void fx_vector_add(fx_vector_t *v, void *item) {
        if (v->size == v->cap) {
                fx_vector_recap(v, 2 * v->cap);
                if (fx_error_check())
                        return;
        }
        v->slots[v->size] = item;
        v->size += 1;
}

void *fx_vector_get(fx_vector_t *v, size_t index) {
        if (index >= v->size) {
                fx_error_raise(FX_EINDEX);
                return NULL;
        }
        return v->slots[index];
}

void fx_vector_set(fx_vector_t *v, size_t index, void *item) {
        if (index >= v->size) {
                fx_error_raise(FX_EINDEX);
                return;
        }
        v->slots[index] = item;
}

void fx_vector_copy(fx_vector_t *dest, fx_vector_t *src) {
        fx_vector_t new_v;

        fx_vector_init(&new_v, src->cap);
        if (fx_error_check())
                return;
        memcpy(new_v.slots, src->slots, sizeof(void *) * src->size);
        new_v.size = src->size;

        fx_vector_free(dest);
        *dest = new_v;
}

fx_vector_t *fx_vector_clone(fx_vector_t *src) {
        fx_vector_t *new_v;

        new_v = malloc(sizeof(*new_v));
        if (!new_v) {
                fx_error_kraise(errno);
                return NULL;
        }
        fx_vector_init(new_v, 0);
        if (fx_error_check()) {
                free(new_v);
                return NULL;
        }
        fx_vector_copy(new_v, src);
        if (fx_error_check()) {
                fx_vector_free(new_v);
                free(new_v);
                return NULL;
        }
        return new_v;
}
