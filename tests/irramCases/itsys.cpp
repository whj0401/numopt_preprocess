#include "iRRAM.h"

using namespace iRRAM;


REAL itsyst(int n)
{
    REAL x = 0.5;
    REAL c = 3.75;
    std::vector<bool> record;
    for (int i = 0; i < n; ++i)
    {
        record.push_back(x.as_double() >= 0.5); // 根据x与0.5大小来判断取正取负，这里加as_doubel是因为REAL无法判断REAL(0.5)>=0.5
        x = c * x * (REAL("1") - x);
    }
    for (int i = n - 1; i >= 0; --i)
    {
        if (record[i])
        {
            x = REAL("0.5") + sqrt(REAL("0.25") - REAL(4.0) / REAL(15.0) * x);
        }
        else
        {
            x = REAL("0.5") - sqrt(REAL("0.25") - REAL(4.0) / REAL(15.0) * x);
        }
    }
    return x;
}