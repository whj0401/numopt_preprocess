#!/bin/bash

bc_file=$1

KLEE_DIR=/home/whj/klee

$KLEE_DIR/Release+Asserts/bin/klee $bc_file

