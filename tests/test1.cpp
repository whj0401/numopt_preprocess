double evaluate(int n, double d)
{
    double res = 0.0;
    int t = 3;
    t = t + 1;
    int p = n;
    p = p + 1;
    n = p;
    int count = p;
    if (n > 0)
    {
        for (int i = 0; i < n; i = i + 1)
        {
            res = res + (1 / i + t);
            count = count + 1;
        }
        
        for (int i = 0; i * i < n; i = i + 1)
        {
            res = res - i - p;
            for (int j = 0; j < n; j = j + 1)
            {
                res = res * 2;
                count = count + 1;
            }
        }
    }
    else
    {
        for (int i = n; i < 0; i = i + 1)
        {
            if (d > 10)
            {
                res = res * 2;
                count = count + 1;
            }
            else
            {
                d = d - i;
                res = res + d;
                count = count + 1;
            }
        }
    }
    if (count > 100)
    {
        res = res - d;
    }
    else
    {
        res = res + d;
    }
    return d - res;
}
