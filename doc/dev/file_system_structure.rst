File system structure
=====================

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

