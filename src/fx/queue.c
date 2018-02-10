#include <fx/queue.h>

#include <signal.h>
#include <fx_error/error.h>

void fx_queue_init(fx_queue_t *q, size_t cap) {
        q->slots = malloc(sizeof(void *) * cap);
        if (!q->slots) {
                fx_error_kraise(errno);
                return;
        }
}
