#!/bin/bash

# NAME
#
#   ctl - Control project's building
#
# SYNOPSIS
#
#   ctl build   build this project
#   ctl clear   clear build files
#
# AUTHORS
#
#   Kevin Leptons <kevin.leptons@gmail.com>

# bash options
set -e

ROOT=$(realpath .)
INC="$ROOT/include"
SRC="$ROOT/src"
DEST="$ROOT/dest"

ctl_build() {
    # prepare
    mkdir -vp $DEST
    cd $DEST

    local BUILD_FLAGS="-DCMAKE_BUILD_TYPE=Debug"
    for opt in "$@"; do
        if [ "$opt" = "--release" ]; then
            BUILD_FLAGS="-DCMAKE_BUILD_TYPE=Release"
        fi
    done

    # use cmake, make to build
    cmake "$BUILD_FLAGS" ..
    make
}

ctl_clear() {
    rm -rf $DEST
    rm -rf cmake-build-debug
    if [ -f core ]; then
        rm core
    fi
}

cmd_build_doc() {
        sphinx-build doc $DEST/doc/html
}

cmd_clear_doc() {
        rm -rf $DEST/doc
}

cmd_open_doc() {
        xdg-open $DEST/doc/html/index.html
}

cmd_init() {
        sudo pip install sphinx
}

ctl_help() {
        local EXE_NAME=$(basename $0)
        echo "USAGE"
        echo "  $EXE_NAME build           Build this project"
        echo "  $EXE_NAME clear           Clear temporary files"
        echo "  $EXE_NAME -h, --help      Show help menu"
}

# parse arguments
case "$1" in
    init) cmd_init;;
    build) ctl_build "${@:2}"; exit 0;;
    clear) ctl_clear; exit 0;;
    doc) cmd_build_doc; exit 0;;
    opendoc) cmd_open_doc; exit 0;;
    cleardoc) cmd_clear_doc; exit 0;;
    -h) ctl_help; exit 0;;
    --help) cmd_help; exit 0;;
    *) ctl_help; exit 1;;
esac
