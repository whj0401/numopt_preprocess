#include <cmath>
#include <iostream>

#include "iRRAM.h"

using namespace iRRAM;

REAL evaluate(int n)
{
    REAL r = 0;
    for (int i = 1; i < n; i++) r = r + REAL(1) / sqrt(REAL(i));
    return r;
}
