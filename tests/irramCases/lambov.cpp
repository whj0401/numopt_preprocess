#include "iRRAM.h"
#include "self_math.h"

using namespace iRRAM;

iRRAM::REAL lambov(int n)
{
    iRRAM::REAL s = exp(1);
    for (int i = n; i >= 0; --i) s = s - 1 / fac(i);
    return s;
}
