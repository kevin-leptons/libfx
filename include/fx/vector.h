#ifndef FX_VECTOR_H
#define FX_VECTOR_H

#include <stdlib.h>

struct fx_vector {
        size_t cap;
        size_t size;
        void **slots;
};
typedef struct fx_vector fx_vector_t;

void fx_vector_init(fx_vector_t *v, size_t cap);
void fx_vector_free(fx_vector_t *v);
void fx_vector_recap(fx_vector_t *v, size_t cap);
void fx_vector_resize(fx_vector_t *v, size_t size);
void fx_vector_add(fx_vector_t *v, void *item);
void *fx_vector_get(fx_vector_t *v, size_t index);
void fx_vector_set(fx_vector_t *v, size_t index, void *item);
void fx_vector_copy(fx_vector_t *dest, fx_vector_t *src);
fx_vector_t *fx_vector_clone(fx_vector_t *src);

#endif
