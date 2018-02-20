fx_file_system_style
====================

NAME
----

fx_file_system_style - fx file system style

SYNOPSIS
--------

.. code-block:: text

        [a-z][a-z0-9_]*\.[h|c]          // for C header and source files
        [a-z][a-z0-9_]*                 // for other files, directories

        [a-z][a-z0-9_]*_d[0-9]{4}       // year postfix
        [a-z][a-z0-9_]*_d[0-9]{6}       // year and month postfix
        [a-z][a-z0-9_]*_d[0-9]{8}       // year, month and day postfix
        [a-z][a-z0-9_]*_t[0-9]{2}       // hour postfix
        [a-z][a-z0-9_]*_t[0-9]{4}       // hour and minute postfix
        [a-z][a-z0-9_]*_t[0-9]{6}       // hour, minute and second postfix
        [a-z][a-z0-9_]*_d[0-9]{14}      // year, month, day, hour, minute
                                        // and second postfix

        .+                              // for special files

DESCRIPTION
-----------

Just lower case, numbers and underscore character are allowed, it is enough to
describe something and still simple enough to read or write. Lower case and
numbers characters are used to describe meaning, underscore character is used
to divide part of name.

Dash character is easy to write and read than underscore character but is is
conflict with identity naming in programs. Then underscore character is
selected instead of dash character to have unified naming for both file system
and identities in programs.

File names with date and time postfix are use for files which have same name
but different created, modified time or it's content is in different date
time.

Exception for special file names. There are file which uses by programs and
using other file names require more cost such as time, documentation or
habits. So it is not requires to compliant naming in this case.


EXAMPLE 01
----------

.. code-block:: text

        // target: valid file names

        error.h                                 // C header
        ring_queue.h                            // C header with multi parts
        ring_queue.c                            // C source

        report_d2018.txt                        // report in 2018 
        report_d201802.txt                      // report in Feb 2018
        report_d20180201.txt                    // report in Feb 01 2018

        log_t23.txt                             // log at 23
        log_t2305.txt                           // log at 23:05
        log_t230509.txt                         // log at 23:05:09

        backup_d20180201230509.txt              // backup in Feb 01 2018
                                                // at 23:05:08

EXAMPLE 02
----------

.. code-block:: text

        // target: invalid file names

        Error.h                                 // contain upper case
        error.H
        ringQueue.h
        RingQueue.h

        ring-queue.h                            // contain dash character
        log-in-today.txt

        log__in.txt                             // dash does not divide
        _log_in.txt                             // anything
        __log_in.txt
        log_in_.txt

EXAMPLE 03
----------

.. code-block:: text

        // target: valid file names for special using

        Makefile                                // contain upper cases but
                                                // it is uses by "make"

        CMakeLists.txt                          // containse upper cases but
                                                // it is uses by "cmake"
