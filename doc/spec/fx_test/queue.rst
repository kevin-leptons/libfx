[-] fx_test_queue
=================

NAME
----

        queue - ring queue.

SYNOPSIS
--------

.. code-block:: c

        #include <fx_test/queue.h>
        // in libfx_test

        void fx_test_queue_init(fx_test_queue_t *q, size_t cap);
        // initialize queue

        void fx_test_queue_free(fx_test_queue_t *q);
        // release resources which uses by queue

        void fx_test_queue_push(fx_test_queue_t *q, void *item);
        // add item into back of queue

        void *fx_test_queue_front(fx_test_queue_t *q);
        // get item in front of queue

        void fx_test_queue_pop(fx_test_queue_t *q);
        // remove an item in front of queue

        void fx_test_queue_clear(fx_test_queue_t *q);
        // make queue is empty

        bool fx_test_queue_empty(fx_test_queue_t *q);
        // check queue is empty or not

        bool fx_test_queue_full(fx_test_queue_t *q);
        // check queue is full or not

DESCRIPTION
-----------

        Queue with fixed capability at initialization and can not change
        capability after that. Only one calling to memory allocator by
        ``fx_test_queue_init()``.

ERROR
-----

        ``fx_test_queue_init()``

                * ``FX_ENOMEM`` not enough memory to allocate

UNDEFINED BEHAVIORS
-------------------

        ``fx_test_queue_init()``

                * **q** points to memory block which uses by other objects
                * **q** points to memory block which is smaller than
                  ``fx_test_queue_t``

        ``fx_test_queue_free()``,
        ``fx_test_queue_push()``,
        ``fx_test_queue_front()``,
        ``fx_test_queue_pop()``,
        ``fx_test_queue_clear()``,
        ``fx_test_queue_empty()``,
        ``fx_test_queue_full()``,

                * **q** is invalid to pass to ``fx_test_queue_init()``
                * **q** is not initialize by ``fx_test_queue_init()``

        ``fx_test_queue_push()``

                * **q** is full

        ``fx_test_queue_front()``,
        ``fx_test_queue_pop()``

                * **q** is empty

BUGS
----

EXAMPLE 01
----------

.. code-block:: c

        // target: initialize, push, front, pop and free queue

        #include <fx_test/queue.h>              // use queue APIs

        fx_test_queue_t q;                      // initialize 
        fx_test_queue_init(&q, 128);

        int one = 1;                            
        int two = 2;
        int three = 3;
        fx_test_queue_push(&q, &one);           // push items to front
        fx_test_queue_push(&q, &two);
        fx_test_queue_push(&q, &three);

        int *item;                              
        item = fx_test_queue_front(&q);         // get front item 
        fx_test_queue_pop(&q);                  // remove front item

        fx_test_free(&q);                       // release resources 
