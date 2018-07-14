#!/bin/bash

code_file=$1

KLEE_DIR=/home/whj/klee

clang++-3.4 -emit-llvm -I $KLEE_DIR/include/klee -g -c $code_file -O0

