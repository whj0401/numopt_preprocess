//
// Created by whj on 8/26/18.
//

#include "self_math.h"

iRRAM::REAL fac(int n)
{
    iRRAM::REAL res = 1;
    for (int i = 2; i <= n; ++i) res = res * i;
    return res;
}

