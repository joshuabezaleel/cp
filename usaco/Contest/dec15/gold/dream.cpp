/*
ID: a_zaky01
PROG: dream
LANG: C++
*/

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <utility>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <limits>
using namespace std;

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
	#define GetTime() fprintf(stderr,"Running time: %.3lf second\n",((double)clock())/CLOCKS_PER_SEC)
#else
	#define debug(...) 
	#define GetTime() 
#endif

//type definitions
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vint;

//abbreviations
#define A first
#define B second
#define MP make_pair
#define PB push_back

//macros
#define REP(i,n) for (int i = 0; i < (n); ++i)
#define REPD(i,n) for (int i = (n)-1; 0 <= i; --i)
#define FOR(i,a,b) for (int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for (int i = (a); (b) <= i; --i)
#define FORIT(it,c) for (__typeof ((c).begin()) it = (c).begin(); it != (c).end(); it++)
#define ALL(a) (a).begin(),(a).end()
#define SZ(a) ((int)(a).size())
#define RESET(a,x) memset(a,x,sizeof(a))
#define EXIST(a,s) ((s).find(a) != (s).end())
#define MX(a,b) a = max((a),(b));
#define MN(a,b) a = min((a),(b));

inline void OPEN(const string &s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

/* -------------- end of azaky's template -------------- */

#define MAXN 1005
const int next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m, d[MAXN][MAXN][2];
char grid[MAXN][MAXN];
vector<pair<pii, int> > q[MAXN * MAXN];

int main(){
	OPEN("dream");
	scanf("%d%d", &n, &m);
	FOR(i, 1, n) FOR(j, 1, m) {
		scanf("%d", &grid[i][j]);
	}
	RESET(d, -1);
	d[1][1][0] = 0;
	q[0].PB(MP(MP(1, 1), 0));
	FOR(curdist, 0, n * m) FORIT(it, q[curdist]) {
		int r = (it->A).A;
		int c = (it->A).B;
		int b = it->B;
		if (d[r][c][b] != curdist) continue;
		if (r == n && c == m) {
			printf("%d\n", curdist);
			return 0;
		}

		// to four direction!
		REP(dir, 4) {
			int nd = curdist + 1;
			int nr = r + next[dir][0];
			int nc = c + next[dir][1];
			int nb = b;
			if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
			if (grid[nr][nc] == 0 || (!nb && grid[nr][nc] == 3)) continue;
			while (grid[nr][nc] == 4) {
				nb = 0;
				nr += next[dir][0];
				nc += next[dir][1];
				nd++;
			}
			if (nr < 1 || nc < 1 || nr > n || nc > m || grid[nr][nc] == 0 || (!nb && grid[nr][nc] == 3)) {
				nr -= next[dir][0];
				nc -= next[dir][1];
				nd--;
			}
			if (grid[nr][nc] == 2) {
				nb = 1;
			}
			if (d[nr][nc][nb] == -1 || d[nr][nc][nb] > nd) {
				d[nr][nc][nb] = nd;
				q[nd].PB(MP(MP(nr, nc), nb));
			}
		}
	}
	puts("-1");
	
	return 0;
}

/* Generated by UsacoTemp v3.0 */
