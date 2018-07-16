#!/bin/bash

for cpp in `ls *.cpp`
do
    ./generate_bc.sh $cpp
    bc=${cpp%.cpp}.bc
    ./run_klee.sh $bc
done

