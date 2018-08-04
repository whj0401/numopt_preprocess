#!/bin/bash

for cpp in `ls *.cpp`
do
    ./generate_bc.sh $cpp
    bc=${cpp%.cpp}.bc
    ./run_klee.sh $bc
done

rm -f klee-last
rm -rf klee-out-*

python3 expr2paths.py `ls *.expr`

for func in `ls *.function`
do
    python3 generate_func.py $func
done
