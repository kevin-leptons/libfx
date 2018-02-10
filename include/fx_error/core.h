#ifndef FX_ERROR_CORE_H
#define FX_ERROR_CORE_H

#include <stdlib.h>
#include <stdbool.h>

struct fx_error {
        const char *const id;
};
typedef struct fx_error fx_error_t;

#define FX_ERROR_DCL(error_name) \
        extern const fx_error_t *const error_name;
#define FX_ERROR_DEF(error_name) \
        const fx_error_t error_name##_ = { .id = #error_name }; \
        const fx_error_t *const error_name = &error_name##_; 

#ifdef _REENTRANT
#define FX_ERROR_STATE_ATTR __thread
#else
#define FX_ERROR_STATE_ATTR
#endif
extern FX_ERROR_STATE_ATTR const fx_error_t *fx_error_state;

FX_ERROR_DCL(FX_ENONE);

void fx_error_raise(const fx_error_t *e);
void fx_error_abort(const fx_error_t *e);
bool fx_error_catch(const fx_error_t *e);
bool fx_error_check();
void fx_error_clear();
const char *fx_error_id(const fx_error_t *e);

#endif
