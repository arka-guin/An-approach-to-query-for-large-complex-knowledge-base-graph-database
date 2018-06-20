#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;
typedef unsigned int uint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 1e5 + 100;

int n, m, node, t;
int a[N], b[N];
vector<int> g[N];

int ts[N], tsLen = 0;
bool used[N];

int edgesTs[N], edgesTsLen = 0;

void dfs(int v) {
    if (used[v]) {
        return ;
    }
    used[v] = true;
    for (int e : g[v]) {
        dfs(b[e]);
        edgesTs[edgesTsLen++] = e;
    }
    ts[tsLen++] = v;
}

int ans[N];
lint cur[N];

const int K = 16;

int precalc[1 << K];

inline int popcount(lint a) {
#define take(a) ((a) & ((1 << K) - 1))
    return precalc[take(a)] + precalc[take(a >> K)] + precalc[take(a >> (2 * K))] + precalc[take(a >> (3 * K))];
#undef take
}

int main() {
    for (int i = 0; i < (1 << K); i++) {
        precalc[i] = __builtin_popcount(i);
    }
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        u--, v--;
        a[i] = u, b[i] = v;
        g[u].pb(i);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i += 64) {
        for (int j = 0; j < n; j++) {
            int v = ts[j];
            cur[v] = 0;
            if (i <= v && v < i + 64) {
                cur[v] = 1ull << (v - i);
            }
        }
        for (int j = 0; j < m; j++) {
            int u = a[edgesTs[j]], v = b[edgesTs[j]];
            cur[u] |= cur[v];
        }
        for (int j = 0; j < n; j++) {
            ans[j] += popcount(cur[j]);
        }
    }
    cin >> t;
    while(t != 0) {
        cin >> node;
	cout << ans[node-1] << endl;
        t--;
    }
    return 0;
}