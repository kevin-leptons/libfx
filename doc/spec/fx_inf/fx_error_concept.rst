.. _fx-error-concept:

fx_error_concept
================

TITLE
-----

fx_error_concept - fx error concept

SCOPE
-----

This section specify error and error handling. That specifications apply for
errors in general programming, not only for specific programming language. In
specific programming language, it must implement follow specifications.
Examples are write in pseudo code.

CONTEXT
-------

#. ``TASK`` is object can be execute.
#. ``WORKER`` is object which execute tasks.
#. ``ERROR`` is a case when worker can not complete ``TASK``.
#. ``INTERNAL_ERROR`` is ``ERROR`` which is causes by programmers. 
#. ``EXTERNAL_ERROR`` is ``ERROR`` which is causes by non programmers.
#. ``ERROR_IDENTITY`` is information represents for ``ERROR``.
#. ``NONE_ERROR`` is special ``ERROR_IDENTITY`` which represents no
   ``ERROR`` occurs.
#. ``ERROR_STATE`` is storage which uses to store ``ERROR_IDENTITY``
   which occurs.
#. ``DISCOVER_ERROR`` mean find ``ERROR`` can be occurs while execute set of
   ``TASK``.
#. ``DEFINE_ERROR`` mean that create ``ERROR_IDENTITY`` correspond with
   ``ERROR``.
#. ``DETECT_ERROR`` mean that detect ``TASK`` will causes ``ERROR``.
#. ``RAISE_ERROR`` mean set ``ERROR_STATE`` by specific ``ERROR_IDENTITY``.
#. ``CATCH_ERROR`` mean test ``ERROR_STATE`` is set by specific
   ``ERROR_IDENTITY``.
#. ``SOLVE_ERROR`` mean try other ``TASK`` to get target result.
#. ``ERROR_HANDLING`` is: ``DISCOVER_ERROR``, ``DEFINE_ERROR``,
   ``DETECT_ERROR``, ``RAISE_ERROR``, ``CATCH_ERROR`` and ``SOLVE_ERROR``.

CLAUSES
-------

#. **MUST**: Provide mechanism to ``DEFINE_ERROR``, ``DETECT_ERROR``,
   ``RAISE_ERROR``, ``CATCH_ERROR`` and ``SOLVE_ERROR``.
#. **MUST**: Provide ``NONE_ERROR``.
#. **MUST**: Provide a ``ERROR_STATE`` for a ``WORKER``.
#. **MUST**: Set ``ERROR_STATE`` by ``NONE_ERROR`` on ``WORKER`` starting.
#. **MUST**: Define all of ``EXTERNAL_ERROR``.
#. **MUST**: ``INTERNAL_ERROR`` must be remove.
#. **MUST**: ``EXTERNAL_ERROR`` should be solve.
#. **MUST**: Do ``RAISE_ERROR`` if ``EXTERNAL_ERROR`` can not be solve.
#. **MUST**: Abort process if ``EXTERNAL_ERROR`` can not be solve ro do
   ``RAISE_ERROR``.
#. **MUST NOT**: Do ``ERROR_HANDLING`` with ``INTERNAL_ERROR``.
#. **MUST NOT**: Define ``ERROR_IDENTITY`` duplication.


EXAMPLE 01
----------

.. code-block:: text

        // target: ERROR

        devide 8 by 0.
        access to 8th index of array have 7 items.
        open not early exist file to read.
        write to file cause full of disk storage.
        connect to not early exist IP address.
        play broken video file.

EXAMPLE 02
----------

.. code-block:: text

        // target: INTERNAL_ERROR

        array a[8] = [1, 2, 3, 4, 5, 6, 7, 8]
        array b[8]

        for i in [0, 8]:                        // on i = 8
                b = 2 * a[i]                    // access to 9th item
                                                // but 9th item is not exist
                                                // mean internal error occurs
                
EXAMPLE 03
----------

.. code-block:: text

        // target: EXTERNAL_ERROR

        array a[] = allocate 2.10^9 bytes       // if computer have not
                                                // enough 2.10^9 free bytes
                                                // mean external error occurs

EXAMPLE 04
----------

.. code-block:: text

        // target: INTERNAL_ERROR must be remove

        // back to EXAMPLE 01, change code to:

        array a[8] = [1, 2, 3, 4, 5, 6, 7, 8]
        array b[8]

        for i in [0, 7]:                        // fixed
                b = 2 * a[i]

EXAMPLE 04
----------

.. code-block:: text

        // target: EXTERNAL_ERROR should be solve

        // back to EXAMPLE 02, change code to:

        array a[] = allocate 2.10^9 bytes       // error occurs
        if can not allocate for a[]             // then it is detect
                try other way                   // and solve
        else
                continue to task                // no error occurs, do normal

EXAMPLE 05
----------

.. code-block:: text

        // target: Do ``RAISE_ERROR`` if ``EXTERNAL_ERROR`` can not be solve.

        array a[] = allocate 2.10^9 bytes       // error occurs
        if can not allocate for a[]             // then it is detect
                set error state by full memory  // and raise
        else
                continue to task                // no error occurs, do normal

EXAMPLE 06
----------

**MUST**: Abort process if ``EXTERNAL_ERROR`` can not be solve ro do
``RAISE_ERROR``.

.. code-block:: text

        array a[] = allocate 2.10^9 bytes       // error occurs
        if can not allocate for a[]             // then it is detect
                abort process                   // but can not solve
                                                // and no parent task
                                                // abort process
        else
                continue to task                // no error occurs, do normal
