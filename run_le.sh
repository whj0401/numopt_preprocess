#!/usr/bin/env bash

iRRAM_HOME=/home/whj/iRRAM

src_file=$1

./my_le $src_file -rose:Cxx -I$iRRAM_HOME/include -Itests/include
cd klee_output
./make_expr.sh
./clean.sh
cd ..
