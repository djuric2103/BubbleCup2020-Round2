// #include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <random>
//#define gauss(n) n*(n+1)/2
using namespace std;

inline long long gauss(long long n) {
    return n * (n + 1) / 2;
}

void matrix_mul(vector<vector<long long>> &a, vector<vector<long long>> &b, vector<vector<long long>> &res, long long m)
{
    vector<vector<long long>> temp(a.size(), vector<long long>(a.size(), 0));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            for (int k = 0; k < b.size(); k++)
            {
                (temp[i][j] += a[i][k] * b[k][j]) %= m;
            }
        }
    }
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            res[i][j] = temp[i][j];
        }
    }
}

void matrix_pow(vector<vector<long long>> &a, vector<vector<long long>> &res, long long n, long long m)
{
    if (n == 1)
    {
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < a.size(); j++)
            {
                res[i][j] = a[i][j];
            }
        }
        return;
    }
    matrix_pow(a, res, n / 2, m);
    matrix_mul(res, res, res, m);
    if (n % 2 == 1)
    {
        matrix_mul(a, res, res, m);
    }
}

long long binary(long long l, long long r, long long target) {
    if (l == r) return l;
    long long q = (l + r) / 2;
    long long val = gauss(q);
    if (val == target) return q;
    if (val < target && gauss(q + 1) > target) return q + 1;
    if (val > target) return binary(l, q - 1, target);
    return binary(q + 1, r, target);
}

long long hash_seq(long long siz, long long b, long long a, long long B, long long M) {
    vector<vector<long long>> mx = 
    {
        { B, 0, 0 },
        { 1, 1, 0 },
        { 0, 1, 1 }
    };

    vector<vector<long long>> mxres(3, vector<long long>(3, 0));
    long long res;

    if (siz != 0)
    {
        matrix_pow(mx, mxres, siz, M);
        res = mxres[1][0] + mxres[2][0];
        res %= M;
    }
    else
    {
        res = 0;
    }

    if (b != -1)res = (res * B + b) % M;
    if (a != -1)res = (res * B + a) % M;
    if (res < 0) res += M;
    return (long long)res;

}

long long hash_simple(long long siz, long long b, long long a, long long B, long long M) {
    long long res = 0;
    for (int i = 1; i <= siz; i++)
    {
        res *= B;
        res += i;
        res %= M;
    }
    if (b != -1)res = (res * B + b) % M;
    if (a != -1)res = (res * B + a) % M;
    if (res < 0) res += M;
    return (long long)res;
}

struct inpu{
    int cas;
    long long n,B,M;
};

bool operator<(inpu a, inpu b){
    if(a.B != b.B) return a.B < b.B;
    if(a.M != b.M) return a.M < b.M;
    return a.n < b.n;
}

int main() {
    int t;
    scanf("%d", &t);
    vector<inpu> in(t);
    for(int i = 0; i < t; ++i){
        in[i].cas = i + 1;
        scanf("%lld%lld%lld", &in[i].n, &in[i].B, &in[i].M);
    }
    // sort(in.begin(), in.end());

    for (int i = 0; i < t; i++) {
        long long n = in[i].n, B=in[i].B, M =in[i].M;
        long long res, a = -1, b = -1;
        if (gauss(n) % 2 == 0) res = binary(1, n, gauss(n) / 2);
        else res = binary(1, n, gauss(n) / 2 + 1);
        long long val = gauss(res);
        if (val != gauss(n) / 2) {
            res -= 2;
            val = gauss(n) / 2 - gauss(res);
            if (val < n) {
                a = val;
            } else {
                if (2 * res + 3 > val) {
                    val += res;
                    res--;
                }
                b = res + 1;
                a = val - b;
                if(!(b > res && a <= n)){
                    a = n;
                    b = val - n;
                }
            }
        }
        printf("Case %d: %lld %lld\n", in[i].cas, gauss(n)%2, hash_seq(res, b, a, B, M));
        //if(i > 700) throw "greska";
    }
    return 0;
}
