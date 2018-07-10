#include "iRRAM.h"
#include <iostream>

iRRAM::REAL f(iRRAM::REAL x)
{
    return 2 * x;
}

//iRRAM::REAL test1(iRRAM::REAL a, int b)
//{
//    for (int i = 0; i < b; ++i)
//    {
//        if (a < b / 2)
//        {
//            a = f(a);
//        }
//        else if (a > b / 2)
//        {
//            a /= 1.1;
//        }
//        else
//        {
//            a *= a;
//        }
//    }
//    return a;
//}

iRRAM::REAL test2(iRRAM::REAL a, iRRAM::REAL b)
{
    bool c1 = false;
    iRRAM::REAL c2, c3 = 1;
    c1 = (a < b);
    c2 = a + b;
    c3 = c2;
    c3 = 2 + a;
    if (c1)
    {
        return c2;
    }
    iRRAM::REAL c4 = f(c2);
//    while(c3 < c4)
//    {
//        c3 = c3 + c4 / 2;
//    }
    if (c3 > c2)
    {
        c4 = c3 + c4;
    }
    else if (c3 < c2)
    {
        c4 = c2 - c3;
    }
    else
    {
        c4 = c4 * 2;
    }
    return c4;
};