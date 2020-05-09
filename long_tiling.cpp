#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxl = 100;
const int maxn = 25;
const int maxk = 15;

int Q;
int N, M;
int mit;
int it[1 + maxk];
int in[1 + maxk][maxl];

bool match[1 + maxl][maxk];

int DP[maxl][1 << maxk];

inline int decode(char c) {
    if (c == 'L') return 0;
    if (c == 'U') return 1;
    if (c == 'R') return 2;
    if (c == 'D') return 3;
    exit(17);
}

inline void readFigure(int n, int i) {
    while (n--) {
        char c; int l;
        cin >> c >> l;
        while (l--) in[i][it[i]++] = decode(c);
    }
}

inline bool place(int i, int y, int x = 0) {
    if (i + it[y] > it[x]) return false;
    set<int> u, v;
    for (int k = 0; k < it[y] - 1; k++)
        u.insert((in[x][1 + i + k] - in[y][1 + k] + 4) % 4), v.insert((in[x][1 + i + k] - (in[y][it[y] - 1 - k] + 2) % 4 + 4) % 4);
    return min(u.size(), v.size()) <= 1;
}

int solve(int i, int mask) {
    int &ret = DP[i][mask];
    if (i == it[0]) return 1;
    if (ret != -1) return ret;

    ret = 0;
    for (int k = 0; k < mit; k++)
        if (!(mask & (1 << k)))
            if (match[i][k])
                ret += solve(i + it[1 + k], mask | (1 << k));
    return ret = !!ret;
}

int main()
{
    ios_base::sync_with_stdio(false);

    cin >> Q;
    while (Q--) {
        mit = 0;
        memset(it, 0, sizeof it);
        memset(DP, 0xFF, sizeof DP);

        cin >> N;
        readFigure(N, 0);
        cin >> M;
        for (int i = 0; i < M; i++) {
            int c, n; cin >> c >> n;
            readFigure(n, 1 + mit);
            for (int j = 1; j < c; j++) {
                it[1 + mit + j] = it[1 + mit];
                for (int k = 0; k < it[1 + mit]; k++)
                    in[1 + mit + j][k] = in[1 + mit][k];
            }
            mit += c;
        }

        for (int i = 0; i < it[0]; i++)
            for (int j = 0; j < mit; j++)
                match[i][j] = place(i, 1 + j);

        int ans = solve(0, 0);
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
