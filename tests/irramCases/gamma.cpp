#include "iRRAM.h"

using namespace iRRAM;


REAL f(REAL x, REAL euler_gamma)
{
    REAL r = gamma((2.0 - euler_gamma + x) / (euler_gamma - 1.0 - x) - 1);
    return r;
}
