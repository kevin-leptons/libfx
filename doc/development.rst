Development
===========

Tutorial
--------

.. code-block:: bash

        sudo apt-get install make       # to run every things automatically
        make config                     # install dependency packages

        make build                      # build every things
        make doc-open                   # open document in browser

        make test                       # test every things
        make install                    # install every things to system

        make pack                       # create distribution files

That are basic commands help you build, test and pack library. To use all of
development commands, you need research about project in next sections.

File system structure
---------------------

.. code-block:: bash

        |
        |-doc                           # document source
        |-include                       # prorotype
        | |-fx_error
        | |-fx_test
        | |-fx
        |
        |-src                           # source code
        | |-fx_error                    # error handling library 
        | |-fx_test                     # testing library
        | |-fx                          # data and algorithm library
        |
        |-dest
        | |-doc
        | | |-text                      # plain text document
        | | |-html                      # web document
        | |
        | |-lib                         # output of library files
        | |-bin                         # outout of executable files
        |

File system naming standard
---------------------------

.. code-block:: bash

        char = [a-z0-9-_.]              # allowed characters
        char+                           # general file name

        year = [0-9]{4}                 # year number
        month = [0-9]{2}                # month number
        day = [0-9]{2}                  # day in month
        hour = [0-9]{2}                 # hour in day
        min = [0-9]{2}                  # minute in hour
        sec = [0-9]{2}                  # second in minute

        char+_ year month day           # with date postfix
        char+_ hour min sec             # with time postfix
        char+_ year month day hour min sec # with date time postfix

        [a-z0-9_]+.[h|c]                # source code file name

That rules apply for both directory and file name, except file name be use by
other packages, for examples:

.. code-block:: bash

        # valid names
        error.h
        dynamic_queue.h
        test_20180115.txt
        test_095502.txt
        test_20180115080002.txt
        Makefile                        # exception, use by make
        CmakeLists.txt                  # exception, use by cmake

        # invalid names
        Error.h
        dynamic-queue.h
        dynamicQueue.h
        DynamicQueue.h

C coding standard
-----------------

.. code-block:: text

        [A-Z0-9_]+                      # macros, constants
        [a-z0-9_]+                      # variables, functions
        for()                           # use for any loop
        //                              # comment in only line
        /* */                           # comment in multi lines
        78 characters per line          # maximum line length
        use "{" for same line           # open structures, functions, blocks
        use "}" for next line           # close structures, functions, blocks
