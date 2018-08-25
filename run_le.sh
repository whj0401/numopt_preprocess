#!/usr/bin/env bash

src_file=$1

cmake-build-debug/my_le $src_file -rose:Cxx -I/home/whj/iRRAM/include
cd klee_output
./make_expr.sh
./clean.sh
cd ..