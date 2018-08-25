#include "iRRAM.h"
#include "../include/self_math.h"

// e_example
iRRAM::REAL e_example(int n)
{
    iRRAM::REAL z = 1;
    for (int i = 1; i < n; i++) z = z + 1 / fac(i);
    return z;
}
