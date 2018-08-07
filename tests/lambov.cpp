#include "iRRAM.h"
#include <cmath>

using namespace iRRAM;

REAL evaluate(int n)
{
    REAL e = exp(REAL(1));
    REAL s = 0, m = 1;
    for (int i = 1; i < n; ++i)
    {
        s = s + m;
        m = m / i;
    }
    return e - s;
}