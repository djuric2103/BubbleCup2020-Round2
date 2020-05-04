#include <bits/stdc++.h>
//#define gauss(n) n*(n+1)/2
using namespace std;

inline long long gauss(long long n) {
    return n * (n + 1) / 2;
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
    int res = 0;
    for (int i = 1; i <= siz; ++i)
        res = (res * B + i) % M;
    if (b != -1)res = (res * B + b) % M;
    if (a != -1)res = (res * B + a) % M;
    return res;

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
    sort(in.begin(), in.end());

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
