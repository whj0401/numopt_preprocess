#include "iRRAM.h"

using namespace iRRAM;

REAL evaluate(REAL x, int degree = 15)
{
    REAL res = 0;
    REAL powx = 1;
    for (int i = 0; i < degree; ++i)
    {
        powx = powx * x;
        res = res + powx;
    }
    return res;
}
