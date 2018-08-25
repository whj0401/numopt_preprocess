/*

iRRAM_REAL.h -- header file for the REAL class of the iRRAM library
 
Copyright (C) 2001-2013 Norbert Mueller
 
This file is part of the iRRAM Library.
 
The iRRAM Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Library General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your
option) any later version.
 
The iRRAM Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
License for more details.
 
You should have received a copy of the GNU Library General Public License
along with the iRRAM Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. 
*/

#ifndef CODE_ANALYSE_REAL_H
#define CODE_ANALYSE_REAL_H

namespace iRRAM
{
    
    
    class REAL
    {
    public:
        
        int value;
// Constructors: -------------------------------
        
        REAL();
        
        REAL(const int i);
        
        REAL(const double d);
        
        REAL(const REAL &y);

// Copy Constructor: ---------------------------
        
        REAL &operator=(const REAL &y);

// Destructor: ---------------------------------
        
        ~REAL();

// Standard Arithmetic: ------------------------
        
        friend REAL operator+(const REAL &x, const REAL &y);
        
        friend REAL operator+(const REAL &x, const int n);
        
        friend REAL operator+(const int n, const REAL &x);
        
        friend REAL operator+(const REAL &x, const double d);
        
        friend REAL operator+(const double d, const REAL &x);
        
        friend REAL &operator+=(REAL &x, const REAL &y);
        
        friend REAL operator-(const REAL &x, const REAL &y);
        
        friend REAL operator-(const REAL &x, const int n);
        
        friend REAL operator-(const int n, const REAL &x);
        
        friend REAL operator-(const REAL &x, const double d);
        
        friend REAL operator-(const double d, const REAL &x);
        
        friend REAL operator-(const REAL &x);
        
        friend REAL operator*(const REAL &x, const REAL &y);
        
        friend REAL operator*(const REAL &x, const int n);
        
        friend REAL operator*(const int n, const REAL &x);
        
        friend REAL operator*(const REAL &x, const double d);
        
        friend REAL operator*(const double d, const REAL &x);
        
        friend REAL &operator*=(REAL &x, const REAL &y);
        
        friend REAL operator/(const REAL &x, const REAL &y);
        
        friend REAL operator/(const REAL &x, const int n);
        
        friend REAL operator/(const int n, const REAL &x);
        
        friend REAL operator/(const REAL &x, const double d);
        
        friend REAL operator/(const double d, const REAL &x);
        
        friend REAL operator<<(const REAL &x, const int n);
        
        friend REAL operator>>(const REAL &x, const int n);
        
        
        friend REAL square(const REAL &x);
        
        friend REAL scale(const REAL &x,
                          const int k);

// Comparisons: --------------------------------
        
        friend bool operator<(const REAL &x, const REAL &y);
        
        friend bool operator<(const REAL &x, const int y);
        
        friend bool operator<(const int x, const REAL &y);
        
        friend bool operator<(const REAL &x, const double y);
        
        friend bool operator<(const double x, const REAL &y);
        
        friend bool operator<=(const REAL &x, const REAL &y);
        
        friend bool operator<=(const REAL &x, const int y);
        
        friend bool operator<=(const int x, const REAL &y);
        
        friend bool operator<=(const REAL &x, const double y);
        
        friend bool operator<=(const double x, const REAL &y);
        
        friend bool operator>(const REAL &x, const REAL &y);
        
        friend bool operator>(const REAL &x, const int y);
        
        friend bool operator>(const int x, const REAL &y);
        
        friend bool operator>(const REAL &x, const double y);
        
        friend bool operator>(const double x, const REAL &y);
        
        friend bool operator>=(const REAL &x, const REAL &y);
        
        friend bool operator>=(const REAL &x, const int y);
        
        friend bool operator>=(const int x, const REAL &y);
        
        friend bool operator>=(const REAL &x, const double y);
        
        friend bool operator>=(const double x, const REAL &y);
        
        friend bool operator==(const REAL &x, const REAL &y);
        
        friend bool operator==(const REAL &x, const int y);
        
        friend bool operator==(const int x, const REAL &y);
        
        friend bool operator==(const REAL &x, const double y);
        
        friend bool operator==(const double x, const REAL &y);
        
        friend bool operator!=(const REAL &x, const REAL &y);
        
        friend bool operator!=(const REAL &x, const int y);
        
        friend bool operator!=(const int x, const REAL &y);
        
        friend bool operator!=(const REAL &x, const double y);
        
        friend bool operator!=(const double x, const REAL &y);
        
        
        friend bool positive(const REAL &x, const int k);

//friend bool  bound       (const REAL& x, const int k);


// conversion to INTEGER is found in iRRAM_INTEGER.h
        operator int() const;
        
        friend REAL round2(const REAL &x);
        
        friend int round(const REAL &x);


#define iRRAM_float_absolute 0
#define iRRAM_float_relative 1
#define iRRAM_float_show 2

// Output: -------------------------------------
        
        friend void rwrite(const REAL &x, const int w);
        
        friend void rwritee(const REAL &x, const int w);
        
        friend void rshow(const REAL &x, const int w);
        
        void rcheck(int n = 50) const;
        
        friend int upperbound(const REAL &x);
        
        friend int size(const REAL &x);

// limit operators: ------------------------


//friend REAL    limit      (REAL f(int, const REAL&, const REAL&),
//                           const REAL& x,
//                           const REAL& y);
//
//friend REAL    limit      (REAL f(int));
//
//friend REAL    limit_hint (REAL f(int, const REAL&),
//                           int hint,
//                           const REAL& x);
//
//friend REAL    limit_hint (REAL f(int, const REAL&, const REAL&),
//                           int hint,
//                           const REAL& x,
//                           const REAL& y);
//
//friend REAL    limit_hint (REAL f(int),
//                           int hint);
//
//friend REAL    iterate     (REAL (*)(REAL&, REAL&, const REAL&),
//                           const REAL&, const REAL&, const REAL&);
//
//friend REAL    iterate     (REAL (*)(REAL&, REAL&),
//                           const REAL&, const REAL&);
//
//friend REAL    iteration   (void (*)(REAL&, REAL&,const int&),
//                           const REAL&, const REAL&,const int&);
    };
    
    inline REAL::~REAL()
    {
    };
    
    inline REAL::REAL()
    {
        value = 0;
    }
    
    inline REAL::REAL(const int i)
    {
        value = i;
    };
    
    inline REAL::REAL(const double d)
    {
        value = d;
    }
    
    inline REAL::REAL(const REAL &y)
    {
        value = y.value;
    };
    
    
    inline REAL &REAL::operator=(const REAL &y)
    {
        value = y.value;
        return (*this);
    };
    
    inline REAL operator<<(const REAL &x, const int n)
    {
        return scale(x, n);
    }
    
    inline REAL operator>>(const REAL &x, const int n)
    {
        return scale(x, -n);
    }
    
    inline REAL operator+(const REAL &x, const REAL &y)
    {
        return REAL(x.value + y.value);
    };
    
    inline REAL operator+(const REAL &x, const int i)
    {
        return REAL(x.value + i);
    };
    
    inline REAL operator+(const int i, const REAL &x)
    {
        return (x + i);
    };
    
    inline REAL operator+(const REAL &x, const double i)
    {
        return REAL(x.value + i);
    };
    
    inline REAL operator+(const double i, const REAL &x)
    {
        return REAL(x.value + i);
    };
    
    inline REAL &operator+=(REAL &x, const REAL &y)
    {
        x.value = x.value + y.value;
        return x;
    };
    
    inline REAL operator-(const REAL &x, const REAL &y)
    {
        return REAL(x.value - y.value);
    };
    
    inline REAL operator-(const REAL &x, const int n)
    {
        return REAL(x.value - n);
    };
    
    inline REAL operator-(const int n, const REAL &x)
    {
        return REAL(n - x.value);
    };
    
    inline REAL operator-(const REAL &x, const double n)
    {
        return REAL(x.value - n);
    };
    
    inline REAL operator-(const double n, const REAL &x)
    {
        return REAL(n - x.value);
    };
    
    inline REAL operator-(const REAL &x)
    {
        return REAL(-x.value);
    };
    
    
    inline REAL operator*(const REAL &x, const REAL &y)
    {
        return REAL(x.value * y.value);
    }
    
    inline REAL operator*(const REAL &x, const int n)
    {
        return REAL(x.value * n);
    }
    
    inline REAL operator*(const int n, const REAL &x)
    {
        return (x * n);
    }
    
    inline REAL operator*(const REAL &x, const double n)
    {
        return REAL(x.value * n);
    }
    
    
    inline REAL operator*(const double n, const REAL &x)
    {
        return (x * n);
    }
    
    inline REAL &operator*=(REAL &x, const REAL &y)
    {
        x = x * y;
        return x;
    }
    
    inline REAL &operator*=(REAL &x, const int n)
    {
        x.value = x.value * n;
        return x;
    }
    
    inline REAL operator/(const REAL &x, const REAL &y)
    {
        return REAL(x.value / y.value);
    };
    
    inline REAL operator/(const int n, const REAL &y)
    {
        return REAL(n) / y;
    }
    
    inline REAL operator/(const REAL &x, const int n)
    {
        return REAL(x.value / n);
    }
    
    inline REAL operator/(const double n, const REAL &y)
    {
        return REAL(n) / y;
    }
    
    inline REAL operator/(const REAL &x, const double n)
    {
        return REAL(x.value / n);
    }
    
    inline REAL &operator/=(REAL &x, const REAL &y)
    {
        x = x / y;
        return x;
    }
    
    inline REAL &operator/=(REAL &x, const int n)
    {
        x = x / n;
        return x;
    }
    
    inline REAL square(const REAL &x)
    {
        return REAL(x.value * x.value);
    }
    
    inline bool operator<(const REAL &x, const REAL &y)
    {
        return x.value < y.value;
    };
    
    
    inline bool operator<(const REAL &x, const int y)
    { return (x < REAL(y)); };
    
    inline bool operator<(const int x, const REAL &y)
    { return (REAL(x) < y); };
    
    inline bool operator<=(const REAL &x, const REAL &y)
    { return (x < y); };
    
    inline bool operator<=(const REAL &x, const int y)
    { return (x <= REAL(y)); };
    
    inline bool operator<=(const int x, const REAL &y)
    { return (REAL(x) <= y); };
    
    inline bool operator>(const REAL &x, const REAL &y)
    { return (y < x); };
    
    inline bool operator>(const REAL &x, const int y)
    { return (x > REAL(y)); };
    
    inline bool operator>(const int x, const REAL &y)
    { return (REAL(x) > y); };
    
    inline bool operator>=(const REAL &x, const REAL &y)
    { return (y < x); };
    
    inline bool operator>=(const REAL &x, const int y)
    { return (x >= REAL(y)); };
    
    inline bool operator>=(const int x, const REAL &y)
    { return (REAL(x) >= y); };
    
    inline bool operator==(const REAL &x, const REAL &y)
    { return (y < x) && (x < y); };
    
    inline bool operator==(const REAL &x, const int y)
    { return (x == REAL(y)); };
    
    inline bool operator==(const int x, const REAL &y)
    { return (REAL(x) == y); };
    
    inline bool operator!=(const REAL &x, const REAL &y)
    { return (y < x) || (x < y); };
    
    inline bool operator!=(const REAL &x, const int y)
    { return (x != REAL(y)); };
    
    inline bool operator!=(const int x, const REAL &y)
    { return (REAL(x) != y); };
    
    
    int pi();
    
    int euler();
    
    int maximum(int, int);
    
    int minimum(int, int);
    
    int abs(int);
    
    int sqrt(int);
    
    int power(int, int);
    
    int exp(int);
    
    int log(int);
    
    int approx(int, int);
    
    int limit(int);
    
    
    int sin(int);
    
    int cos(int);
    
    int tan(int);
    
    int cot(int);
    
    int sec(int);
    
    int cosec(int);
    
    int cotan(int);
    
    int asin(int);
    
    int acos(int);
    
    int atan(int);
    
    int acot(int);
    
    int sinh(int);
    
    int cosh(int);
    
    int tanh(int);
    
    int coth(int);
    
    int sech(int);
    
    int cosech(int);
    
    int asinh(int);
    
    int acosh(int);
    
    int atanh(int);
    
    int acoth(int);
    
    int asech(int);
    
    int acosech(int);
    
    int gamma(int);
    
    int fac(int);
    
    int gammb(int);
    
    int gamm(int);
    
    int gammac(int);
    
    REAL real_pi()
    {
        return REAL(pi());
    }
    
    REAL real_euler()
    {
        return REAL(euler());
    }
    
    REAL maximum(const REAL &a, const REAL &b)
    {
        return REAL(maximum(a.value, b.value));
    }
    
    REAL minimum(const REAL &a, const REAL &b)
    {
        return REAL(minimum(a.value, b.value));
    }
    
    REAL abs(const REAL &a)
    {
        return REAL(abs(a.value));
    }
    
    REAL sqrt(const REAL &a)
    {
        return REAL(sqrt(a.value));
    }
    
    REAL power(const REAL &a, const REAL &b)
    {
        return REAL(power(a.value, b.value));
    }
    
    REAL exp(const REAL &a)
    {
        return REAL(exp(a.value));
    }
    
    REAL log(const REAL &a)
    {
        return REAL(log(a.value));
    }
    
    REAL approx(const REAL &a, const REAL &b)
    {
        return REAL(approx(a.value, b.value));
    }
    
    REAL limit(const REAL &a)
    {
        return REAL(limit(a.value));
    }
    
    REAL sin(const REAL &a)
    {
        return REAL(sin(a.value));
    }
    
    REAL cos(const REAL &a)
    {
        return REAL(cos(a.value));
    }
    
    REAL tan(const REAL &a)
    {
        return REAL(tan(a.value));
    }
    
    REAL cot(const REAL &a)
    {
        return REAL(cot(a.value));
    }
    
    REAL sec(const REAL &a)
    {
        return REAL(sec(a.value));
    }
    
    REAL cosec(const REAL &a)
    {
        return REAL(cosec(a.value));
    }
    
    REAL cotan(const REAL &a)
    {
        return REAL(cotan(a.value));
    }
    
    REAL asin(const REAL &a)
    {
        return REAL(asin(a.value));
    }
    
    REAL acos(const REAL &a)
    {
        return REAL(acos(a.value));
    }
    
    REAL atan(const REAL &a)
    {
        return REAL(atan(a.value));
    }
    
    REAL acot(const REAL &a)
    {
        return REAL(acot(a.value));
    }
    
    REAL sinh(const REAL &a)
    {
        return REAL(sinh(a.value));
    }
    
    REAL cosh(const REAL &a)
    {
        return REAL(cosh(a.value));
    }
    
    REAL tanh(const REAL &a)
    {
        return REAL(tanh(a.value));
    }
    
    REAL coth(const REAL &a)
    {
        return REAL(coth(a.value));
    }
    
    REAL sech(const REAL &a)
    {
        return REAL(sech(a.value));
    }
    
    REAL cosech(const REAL &a)
    {
        return REAL(cosech(a.value));
    }
    
    REAL asinh(const REAL &a)
    {
        return REAL(asinh(a.value));
    }
    
    REAL acosh(const REAL &a)
    {
        return REAL(acosh(a.value));
    }
    
    REAL atanh(const REAL &a)
    {
        return REAL(atanh(a.value));
    }
    
    REAL acoth(const REAL &a)
    {
        return REAL(acoth(a.value));
    }
    
    REAL asech(const REAL &a)
    {
        return REAL(asech(a.value));
    }
    
    REAL acosech(const REAL &a)
    {
        return REAL(acosech(a.value));
    }
    
    REAL gamma(const REAL &x)
    {
        return REAL(gamma(x.value));
    }
    
    REAL fac(const REAL &n)
    {
        return REAL(fac(n.value));
    }
} // namespace iRRAM

#endif //CODE_ANALYSE_REAL_H
