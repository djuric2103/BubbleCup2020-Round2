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

// long long mod = 998244353;
long long mod = 1000000007;
vector<long long> fact(1000001);
vector<long long> invFact(1000001);

vector<int> setSize(100000, 1);

long long gcd(long long a, long long b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

long long binpow(long long x, long long k)
{
    if (k == 0)
    {
        return 1LL;
    }
    long long temp = binpow(x, k / 2);
    if (k % 2 == 1)
    {
        return (((temp * temp) % mod) * x) % mod;
    }
    else
    {
        return (temp * temp) % mod;
    }
}

long long modular_inverse(long long x)
{
    return binpow(x, mod - 2);
}

long long binomial(long long n, long long k)
{
    long long rez = 1;
    for (long long i = n - k + 1; i <= n; i++)
    {
        rez *= i;
        rez %= mod;
    }
    long long temp = 1;
    for (long long i = 1; i <= k; i++)
    {
        temp *= i;
        temp %= mod;
    }
    rez *= modular_inverse(temp);
    rez %= mod;
    return rez;
}

int fi(int a, vector<int> &p)
{
    if (p[a] != p[p[a]])
    {
        p[a] = fi(p[a], p);
    }
    return p[a];
}

void uni(int a, int b, vector<int> &p)
{
    int x = fi(a, p), y = fi(b, p);
    if (x != y)
    {
        p[x] = y;
        setSize[y] += setSize[x];
    }
}

long long euclidianDistanceSquared(pair<int, int> a, pair<int, int> b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

double euclidianDistanceSquared(pair<double, double> a, pair<double, double> b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

double euclidianDistance(pair<double, double> a, pair<double, double> b)
{
    return sqrt(euclidianDistanceSquared(a, b));
}

bool circleIntersections(pair<double, double> pos1, double r1, pair<double, double> pos2, double r2, pair<double, double> &int1, pair<double, double> &int2)
{
    double d = euclidianDistance(pos1, pos2);
    if (r1 + r2 < d || d < fabs(r1 - r2))
    {
        return false;
    }
    double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    double h = sqrt(r1 * r1 - a * a);
    pair<double, double> pos3 = { pos1.first + a * (pos2.first - pos1.first) / d, pos1.second + a * (pos2.second - pos1.second) / d };
    int1.first = pos3.first + h * (pos2.second - pos1.second) / d;
    int1.second = pos3.second - h * (pos2.first - pos1.first) / d;
    int2.first = pos3.first - h * (pos2.second - pos1.second) / d;
    int2.second = pos3.second + h * (pos2.first - pos1.first) / d;
    return true;
}

class SegmentTree
{
public:
    class Node
    {
    public:
        vector<int> value;
        Node *l, *r;
        int left, right;

        Node(int x, int y)
        {
            value = vector<int>(26, 0);
            l = nullptr;
            r = nullptr;
            left = x;
            right = y;
        }

        void update(int p, char c)
        {
            if (left > p || p > right)
            {
                return;
            }
            if (left == p && p == right)
            {
                for (int i = 0; i < 26; i++)
                {
                    value[i] = 0;
                }
                value[c - 'a'] = 1;
                return;
            }
            if (l == nullptr)
            {
                int mid = (left + right) / 2;
                l = new Node(left, mid);
                r = new Node(mid + 1, right);
            }
            l->update(p, c);
            r->update(p, c);
            for (int i = 0; i < 26; i++)
            {
                value[i] = l->value[i] + r->value[i];
            }
        }

        int query(int x, int y)
        {
            if (left > y || x > right)
            {
                return 0;
            }
            if (x <= left  && right <= y)
            {
                int rez = 0;
                for (int i = 0; i < 26; i++)
                {
                    if (value[i] != 0)
                    {
                        rez |= (1 << i);
                    }
                }
                return rez;
            }
            if (l == nullptr)
            {
                return 0;
            }
            return l->query(x, y) | r->query(x, y);
        }
    };

    Node *root;
    SegmentTree(int n)
    {
        root = new Node(0, n - 1);
    }

    void update(int p, char c)
    {
        root->update(p, c);
    }

    int query(int x, int y)
    {
        return root->query(x, y);
    }
};

void put_permutations(vector<int> &v, vector<__int128> &res)
{
    vector<int> temp;
    __int128 num;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == 0)
        {
            continue;
        }
        temp.push_back(i);
    }
    do
    {
        num = 0;
        for (int i = 0; i < temp.size(); i++)
        {
            if (v[temp[i]] < 10)
            {
                num *= 100;
                num += 10 * v[temp[i]] + temp[i];
            }
            else
            {
                num *= 1000;
                num += 10 * v[temp[i]] + temp[i];
            }
        }
        res.push_back(num);
    } while (next_permutation(temp.begin(), temp.end()));
}

void make_counts(vector<int> &v, __int128 x)
{
    __int128 temp = x;
    int a, b, digits = 0;
    while (temp != 0)
    {
        temp /= 10;
        digits++;
    }
    for (int i = 0; i < 10; i++)
    {
        v[i] = 0;
    }
    while (x != 0)
    {
        a = x % 10;
        x /= 10;
        b = x % 10;
        x /= 10;
        if (a == 1 && digits % 2 == 1)
        {
            b += 10 * (x % 10);
            x /= 10;
        }
        v[a] = b;
    }
}

string decimal_string(__int128 x)
{
    string s = "";
    __int128 reversed = 0;
    int digits = 0;
    while (x != 0)
    {
        reversed *= 10;
        reversed += x % 10;
        x /= 10;
        digits++;
    }
    while (digits != 0)
    {
        s.append("x");
        s[s.size() - 1] = reversed % 10 + '0';
        reversed /= 10;
        digits--;
    }
    return s;
}

bool check_invalid(__int128 x, int f)
{
    while (x != 0)
    {
        if ((x % 10) == f)
        {
            return true;
        }
        x /= 10;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(12);
    

    vector<__int128> possibles = { 22, 10213223, 10311233, 10313314, 10313315, 10313316, 10313317, 10313318, 10313319, 21322314, 21322315, 21322316, 21322317, 21322318, 21322319, 31123314, 31123315, 31123316, 31123317, 31123318, 31123319, 31331415, 31331416, 31331417, 31331418, 31331419, 31331516, 31331517, 31331518, 31331519, 31331617, 31331618, 31331619, 31331718, 31331719, 31331819, 1031223314, 1031223315, 1031223316, 1031223317, 1031223318, 1031223319, 3122331415, 3122331416, 3122331417, 3122331418, 3122331419, 3122331516, 3122331517, 3122331518, 3122331519, 3122331617, 3122331618, 3122331619, 3122331718, 3122331719, 3122331819, 10413223241516, 10413223241517, 10413223241518, 10413223241519, 10413223241617, 10413223241618, 10413223241619, 10413223241718, 10413223241719, 10413223241819, 41322324151617, 41322324151618, 41322324151619, 41322324151718, 41322324151719, 41322324151819, 41322324161718, 41322324161719, 41322324161819, 41322324171819, 1051322314251617, 1051322314251618, 1051322314251619, 1051322314251718, 1051322314251719, 1051322314251819, 1051322325161718, 1051322325161719, 1051322325161819, 1051322325171819, 5132231425161718, 5132231425161719, 5132231425161819, 5132231425171819, 5132232516171819, 106132231415261718, 106132231415261719, 106132231415261819, 106132231426171819, 106132231526171819, 613223141526171819, 1011112131415161718, 1011112131415161719, 1011112131415161819, 1011112131415171819, 1011112131416171819, 1011112131516171819, 1011112141516171819, 1011113141516171819, 1111213141516171819 };
    
    // 10713223141516271819
    possibles.push_back(1071322314151);
    possibles[possibles.size() - 1] *= 10000000;
    possibles[possibles.size() - 1] += 6271819;
    int t, f;
    cin >> t;
    long long n;
    vector<int> v(10);
    vector<__int128> res;
    for (int i = 0; i < t; i++)
    {
        cin >> n >> f;
        res.clear();
        for (int i = 0; i < possibles.size(); i++)
        {
            if (check_invalid(possibles[i], f))
            {
                continue;
            }
            make_counts(v, possibles[i]);
            put_permutations(v, res);
        }
        sort(res.begin(), res.end());
        if (n > res.size())
        {
            throw 20;
        }
        cout << decimal_string(res[n - 1]) << '\n';
    }

    return 0;
}
