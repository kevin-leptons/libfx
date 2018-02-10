#include <fx_error/core.h>

#include <signal.h>

FX_ERROR_DEF(FX_ENONE);

const FX_ERROR_STATE_ATTR fx_error_t *fx_error_state = &FX_ENONE_;

inline void fx_error_raise(const fx_error_t *e) {
        fx_error_state = e; 
}

inline bool fx_error_catch(const fx_error_t *e) {
        return fx_error_state == e; 
}

inline bool fx_error_check() {
        return fx_error_state != FX_ENONE; 
}

inline void fx_error_clear() { 
        fx_error_state = FX_ENONE; 
}

inline const char *fx_error_id(const fx_error_t *e) {
        return e->id; 
}
