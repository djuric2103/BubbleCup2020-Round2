#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn = 200 + 17;
const int maxk = maxn * (maxn - 1) / 3;

const int fmul = 17;
const int MOD  = 7 * 17 * (1 << 23) + 1;

int fx(int l, int r);
string frec(int l, int r);
int gx(int wi, int w);
string grec(int wi, int w, int widx);

int N;
string S;

int where[maxn][maxn];

/// {hash, ln, l}
int sz;
vector<piii> vx;

int  fc[maxn][maxn], gc[maxk][maxn], lc[maxk][maxn];
bool fv[maxn][maxn], gv[maxk][maxn];

inline string itos(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

inline string substring(int l, int r) {
    string ret = "";
    for (int i = l; i <= r; i++) ret += S[i];
    return ret;
}

inline void update(int &u, int v, int x, int y, int z) {
    if (u <= v) return;
    u = v;
    lc[x][y] = 1 + lc[z][y];
}

inline void init() {
    N = S.size();
    memset(fv, 0, sizeof fv);
    memset(gv, 0, sizeof gv);
    vx.clear();

    for (int i = 0; i < N; ++i) {
        ll cr = 0;
        int lb = min(N, i + N / 2 + 2);
        for (int j = i; j < lb; ++j)
            cr = (cr * fmul + S[j]) % MOD,
            vx.push_back({cr, {j - i, i}});
    }
    sz = vx.size();
    sort(vx.begin(), vx.end());
    for (int i = 0; i < sz; ++i) where[vx[i].s.s][vx[i].s.s + vx[i].s.f] = i;
}

int fx(int l, int r) {
    int &ret = fc[l][r];
    if (l > r) return ret = 0;
    if (fv[l][r]) return ret;
    fv[l][r] = true;
    int ln = r - l + 1;

    ret = ln;
    for (int i = 1; i < ln; ++i) ret = min(ret, fx(l, l + i - 1) + fx(l + i, r));
    for (int i = 1; i < ln; ++i) {
        int fl = l, fr = l + i - 1;
        int sl = r - i + 1, sr = r;
        if (fr >= sl) break;
        int fw = where[fl][fr], sw = where[sl][sr];
        if (vx[fw].f == vx[sw].f) ret = min(ret, gx(fw, sl - 1) + 3 + fx(fl, fr));
    }
    return ret;
}

string frec(int l, int r) {
    if (l > r) return "";
    int ln = r - l + 1;

    if (fx(l, r) == ln) return S.substr(l, ln);
    for (int i = 1; i < ln; ++i) if (fc[l][r] == fc[l][l + i - 1] + fc[l + i][r]) return frec(l, l + i - 1) + frec(l + i, r);
    for (int i = 1; i < ln; ++i) {
        int fl = l, fr = l + i - 1;
        int sl = r - i + 1, sr = r;
        if (fr >= sl) break;
        int fw = where[fl][fr], sw = where[sl][sr];
        if (vx[fw].f == vx[sw].f)
            if (fc[l][r] == gc[fw][sl - 1] + 3 + fc[fl][fr]) return "[" + frec(fl, fr) + "]" + to_string(1 + lc[fw][sl - 1]) + grec(fw, sl - 1, 1);
    }

    /// assert(false);
}

int gx(int wi, int w) {
    if (gv[wi][w]) return gc[wi][w];
    gv[wi][w] = true;
    lc[wi][w] = 1;
    int cl = vx[wi].s.s, cr = vx[wi].s.s + vx[wi].s.f;

    if (w == cr) gc[wi][w] = 0;
    else gc[wi][w] = 3 + fx(cr + 1, w);

    for (int i = wi + 1; i < sz; ++i) {
        int nl = vx[i].s.s, nr = vx[i].s.s + vx[i].s.f;
        if (vx[i].f != vx[wi].f) break;
        if (nr > w) break;

        if (nl > cr) {
            int v = gx(i, w);
            if (cr + 1 != nl) v += 3 + fx(cr + 1, nl - 1);
            update(gc[wi][w], v, wi, w, i);
        }
    }
    return gc[wi][w];
}

string grec(int wi, int w, int widx) {
    int cl = vx[wi].s.s, cr = vx[wi].s.s + vx[wi].s.f;

    if (w == cr) return "";
    if (gc[wi][w] == fc[cr + 1][w] + 3) return "{" + frec(cr + 1, w) + "}" + to_string(widx);

    for (int i = wi + 1; i < sz; ++i) {
        int nl = vx[i].s.s, nr = vx[i].s.s + vx[i].s.f;
        if (vx[i].f != vx[wi].f)
        if (nr > w) break;

        if (nl > cr) {
            int v = gc[i][w];
            if (cr + 1 != nl) {
                v += fc[cr + 1][nl - 1] + 3;
                if (gc[wi][w] == v) return "{" + frec(cr + 1, nl - 1) + "}" + to_string(widx) + grec(i, w, 1 + widx);
            }

            if (gc[wi][w] == v) return grec(i, w, 1 + widx);
        }
    }

    /// assert(false);
}

int main()
{
    ios_base::sync_with_stdio(false);

    while (cin >> S) {
        init();
        cout << fx(0, N - 1) << " " << frec(0, N - 1) << endl;
    }

    return 0;
}
