#include "iRRAM.h"

using namespace iRRAM;

REAL abs(REAL r, REAL i)
{
    return sqrt((r * r) + (i * i));
}

REAL midarc_real(REAL z1real, REAL z1image, REAL z2real, REAL z2image)
{
//    if(abs(z1real, z1image)!=1 || abs(z2real, z2image)!=1)
//        return 1;
    REAL r = z1real + z2real;
    REAL i = z1image + z2image;
    REAL len = abs(r, i);
    return r / len;
}

REAL midarc_image(REAL z1real, REAL z1image, REAL z2real, REAL z2image)
{
    REAL r = z1real + z2real;
    REAL i = z1image + z2image;
    REAL len = abs(r, i);
    return i / len;
}