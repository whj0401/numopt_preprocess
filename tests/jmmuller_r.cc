#include "iRRAM.h"

using namespace iRRAM;

/* Compute iteration by J.M.Muller */

REAL evaluate(int count)
{
    
    REAL a = REAL(10) / 2, b = REAL(66) / 11, c;
    long i = 0;
    while (i < count)
    {
        c = 111 - (1130 - 3000 / a) / b;
        a = b;
        b = c;
        i++;
    }
    i = 0;
    while (i < count)
    {
        c = 3000 / (1130 - (111 - b) * a);
        b = a;
        a = c;
    }
    return c;
}
