//
// Created by whj on 6/13/18.
//

#include "iRRAM.h"

using namespace iRRAM;

REAL f(REAL a, REAL b)
{
    REAL sum = 0;
    while (sum < a * b)
    {
        sum += a;
    }
    
    do
    {
        sum = sum - b;
    } while (sum > a * b);
    return sum;
}