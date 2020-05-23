/*
ID: a_zaky01
PROG: skilevel
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

#define MAXN 505
#define MAXT 500500

int n, m, t, a[MAXN][MAXN];
int idx[MAXN][MAXN], p[MAXT], size[MAXT], ans[MAXT], visited[MAXT];
vector <pair<int,pii> > edge;
vector <int> adj[MAXT];

int findSet (int x) {
	return p[x] == x ? x : p[x] = findSet(p[x]);
}

void dfs (int par, int v, int diff) {
	if (visited[v]) return;
	
	visited[v] = 1;
	ans[v] = diff;
	
	FORIT(it, adj[v]) {
		if (*it != par) dfs (v, *it, diff);
	}
}

int main(){
	OPEN("skilevel");
	
	scanf("%d%d%d",&n,&m,&t);
	FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
	
	FOR(i,1,n) FOR(j,1,m) {
		idx[i][j] = (i-1)*m + (j-1);
		p[idx[i][j]] = idx[i][j];
		size[idx[i][j]] = 1;
	}
	
	FOR(i,1,n) FOR(j,1,m) {
		if (i < n) {
			int diff = a[i][j] - a[i+1][j];
			if (diff < 0) diff *= -1;
			edge.PB(MP(diff,MP(idx[i][j],idx[i+1][j])));
		}
		if (j < m) {
			int diff = a[i][j] - a[i][j+1];
			if (diff < 0) diff *= -1;
			edge.PB(MP(diff,MP(idx[i][j],idx[i][j+1])));
		}
	}
	sort(ALL(edge));
	
	//fprintf(stderr,"hello!");
	
	FORIT(it,edge) {
		int diff = it->first;
		int x = (it->second).first, y = (it->second).second;
		
		if (findSet(x) == findSet(y)) continue;
		
		size[findSet(x)] += size[findSet(y)];
		p[findSet(y)] = findSet(x);
		
		if (size[findSet(x)] >= t) {
			dfs(x, x, diff);
			dfs(y, y, diff);
		}
		
		adj[x].PB(y);
		adj[y].PB(x);
	}
	
	ll totalAns = 0;
	
	FOR(i,1,n) FOR(j,1,m) {
		int isStartingPoint;
		scanf("%d",&isStartingPoint);
		if (isStartingPoint) {
			totalAns += (ll) ans[idx[i][j]];
		}
	}
	
	cout << totalAns << endl;
	
	return 0;
}

/* Generated by UsacoTemp v3.0 */