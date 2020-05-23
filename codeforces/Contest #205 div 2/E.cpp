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

//abbreviations
#define A first
#define B second
#define MP make_pair
#define PB push_back
#define LLD "%I64d"

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

/* -------------- end of azaky's template -------------- */

char s[1111111];
int n, ind[1111111], oud[1111111], ans, x, vis[1111111];

void dfs(int v){
	if (vis[v]) return;
	vis[v] = 1;
	if (ind[v] == 2 || oud[v] == 2) return;
	dfs((v+1)%n);
	dfs((v+n-1)%n);
}

int main(){
	scanf("%s",s);
	n = strlen(s);
	REP(i,n){
		if (s[i] == '0'){
			ind[(i+1)%n] ++;
			oud[i] ++;
		}
		else {
			ind[i] ++;
			oud[(i+1)%n] ++;
		}
	}
	ans = 0;
	REP(i,n){
		if (vis[i]) continue;
		if (ind[i] == oud[i]){
			ans++;
			dfs(i);
		}
	}
	x = -1;
	REP(i,n) if (vis[i]){
		x = i;
		continue;
	}
	if (x == -1){
		printf("%d\n",n/2);
	}
	else {
		int _x = x;
		x = (x+1) % n;
		while (x != _x){
			while (x != _x && vis[x]) x = (x+1) % n;
			if (x == _x) break;
			int cot = 0;
			while (!vis[x]){
				cot++;
				x = (x+1) % n;
			}
			ans += (cot+1) / 2;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}