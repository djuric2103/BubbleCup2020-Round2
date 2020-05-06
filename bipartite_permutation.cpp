#include <bits/stdc++.h>

using namespace std;

inline long long gauss(long long n) {
    return n * (n + 1) / 2;
}

void
matrix_mul(vector<vector<long long>> &a, vector<vector<long long>> &b, vector<vector<long long>> &res, long long m) {
    vector<vector<long long>> temp(a.size(), vector<long long>(a.size(), 0));
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b[0].size(); ++j)
            for (int k = 0; k < b.size(); ++k)
                (temp[i][j] += a[i][k] * b[k][j]) %= m;

    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b[0].size(); ++j)
            res[i][j] = temp[i][j];
}

void matrix_pow(vector<vector<long long>> &a, vector<vector<long long>> &res, long long n, long long m) {
    if (n == 1) {
        for (int i = 0; i < a.size(); ++i)
            for (int j = 0; j < a.size(); ++j)
                res[i][j] = a[i][j];
        return;
    }
    matrix_pow(a, res, n / 2, m);
    matrix_mul(res, res, res, m);
    if (n % 2 == 1) matrix_mul(a, res, res, m);
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

long long hash_seq(vector<long long> vec, long long B, long long M) {
    long long siz = vec[0];
    vector<vector<long long>> mx = {{B, 0, 0},
                                    {1, 1, 0},
                                    {0, 1, 1}};
    vector<vector<long long>> mxres(3, vector<long long>(3, 0));
    long long res;
    if (siz != 0) {
        matrix_pow(mx, mxres, siz, M);
        res = mxres[1][0] + mxres[2][0];
        res %= M;
    } else res = 0;
    for (int i = 1; i < vec.size(); ++i) res = (res * B + vec[i]) % M;
    if (res < 0) res += M;
    return (long long) res;
}

vector<long long> find_seq(long long seq, long long n) {
    vector<long long> vec;
    if (gauss(n) / 2 == gauss(seq)) {
        vec.push_back(seq);
        return vec;
    }
    long long diff = gauss(n) / 2 - gauss(seq - 2);
    if (diff < n) {
        vec.push_back(seq - 2), vec.push_back(diff);
        return vec;
    }
    long long k = 1;
    for (--seq, diff = gauss(n) / 2 - gauss(seq); diff < seq + 1 || diff > gauss(n) - gauss(n - k); diff += seq, ++k, --seq);
    vec.push_back(seq);
    vec.push_back(diff - (gauss(n) - gauss(n - k + 1)));
    for (int i = n - k + 2; i <= n; ++i) vec.push_back(i);
    return vec;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        long long n, B, M;
        scanf("%lld%lld%lld", &n, &B, &M);
        long long seq;
        if (gauss(n) % 2 == 0) seq = binary(1, n, gauss(n) / 2);
        else seq = binary(1, n, gauss(n) / 2 + 1);
        if (gauss(n) / 2 - gauss(seq) < 0) --seq;
        printf("Case %d: %lld %lld\n", i + 1, gauss(n) % 2, hash_seq(find_seq(seq, n), B, M));
    }
    return 0;
}
