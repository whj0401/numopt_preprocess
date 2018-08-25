#include "iRRAM.h"

iRRAM::REAL evaluate(int n)
{
    int i = 1;
    iRRAM::REAL initval = 0;
    for (i = 1; i < n; ++i)
    {
        initval += (iRRAM::REAL(1) / iRRAM::REAL(i * i));
    }
    return initval;
}