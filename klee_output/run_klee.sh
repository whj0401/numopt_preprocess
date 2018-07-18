#!/bin/bash

bc_file=$1

KLEE_DIR=/home/whj/klee

$KLEE_DIR/Release+Asserts/bin/klee -check-div-zero=0 -check-overshift=0 $bc_file

mv expression.txt ${bc_file%.bc}.expr

#rm -f klee-last
#rm -rf klee-out-*
