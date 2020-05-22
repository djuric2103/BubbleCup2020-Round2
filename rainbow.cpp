#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <set>
#include <queue>
#include <iomanip>
#include <math.h>
#include <fstream>

using namespace std;

long long mod = 1000002015;

// sn = sum(i), i = 0 to n-1
// sq = sum(q^i), i = 0 to n-1
// sqq = sum(i * q^i), i = 0 to n-1
// qpow[i] = q^i
long long q, n, sn, sq, sqq;
vector<long long> qpow(100000);

class Matrix
{
public:
    // M(i, j) = a + i * b + c * Q^j + i * d * Q^j
    long long a, b, c, d;

    static void init(long long _q, long long _n)
    {
        if (qpow.size() < _n)
        {
            qpow.resize(_n);
        }
        q = _q;
        n = _n;
        sn = (n * (n - 1) / 2) % mod;
        sq = 0;
        sqq = 0;
        long long _qpow = 1;
        for (int i = 0; i < n; i++)
        {
            qpow[i] = _qpow;
            (sq += _qpow) %= mod;
            (sqq += i * _qpow) %= mod;
            (_qpow *= q) %= mod;
        }
    }

    static Matrix multiply(Matrix &x, Matrix &y)
    {
        Matrix res;
        res.a = ((n * x.a) % mod * y.a) % mod;
        res.a += ((x.a * y.b) % mod * sn) % mod;
        res.a %= mod;
        res.a += ((x.c * y.a) % mod * sq) % mod;
        res.a %= mod;
        res.a += ((x.c * y.b) % mod * sqq) % mod;
        res.a %= mod;
        
        res.b = ((n * x.b) % mod * y.a) % mod;
        res.b += ((x.b * y.b) % mod * sn) % mod;
        res.b %= mod;
        res.b += ((x.d * y.a) % mod * sq) % mod;
        res.b %= mod;
        res.b += ((x.d * y.b) % mod * sqq) % mod;
        res.b %= mod;
        
        res.c = ((n * x.a) % mod * y.c) % mod;
        res.c += ((x.a * y.d) % mod * sn) % mod;
        res.c %= mod;
        res.c += ((x.c * y.c) % mod * sq) % mod;
        res.c %= mod;
        res.c += ((x.c * y.d) % mod * sqq) % mod;
        res.c %= mod;
        
        res.d = ((n * x.b) % mod * y.c) % mod;
        res.d += ((x.b * y.d) % mod * sn) % mod;
        res.d %= mod;
        res.d += ((x.d * y.c) % mod * sq) % mod;
        res.d %= mod;
        res.d += ((x.d * y.d) % mod * sqq) % mod;
        res.d %= mod;

        return res;
    }

    static Matrix pow(Matrix &a, long long k)
    {
        if (k == 1)
        {
            return a;
        }
        Matrix res = pow(a, k / 2);
        res = multiply(res, res);
        if (k % 2 == 1)
        {
            res = multiply(res, a);
        }
        return res;
    }

    long long at(long long i, long long j)
    {
        // M(i, j) = a + i * b + c * Q^j + i * d * Q^j
        return (((a + i * b) % mod + c * qpow[j]) % mod + ((i * d) % mod * qpow[j]) % mod) % mod;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    // ifstream cin("in.txt");
    // ofstream cout("out.txt");
    

    long long n, k, d, q, m;
    while (cin >> n)
    {
        cin >> k >> d >> q >> m;
        Matrix::init(q, n);
        Matrix x;
        x.a = 0;
        x.b = d;
        x.c = 1;
        x.d = 0;
        x = Matrix::pow(x, k);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            cout << x.at(a, b) << '\n';
        }
    }

    return 0;
}
