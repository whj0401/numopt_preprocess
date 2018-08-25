#include "iRRAM.h"

using namespace iRRAM;

/* Compute iteration by J.M.Muller */

iRRAM::REAL evaluate(int count)
{
    
    iRRAM::REAL a = REAL(10) / 2;
    iRRAM::REAL b = REAL(66) / 11;
    iRRAM::REAL c;
    for (int i = 0; i < count; i++)
    {
        c = 111 - (1130 - 3000 / a) / b;
        a = b;
        b = c;
    }
    for (int i = 0; i < count; i++)
    {
        c = 3000 / (1130 - (111 - b) * a);
        b = a;
        a = c;
    }
    return c;
}
