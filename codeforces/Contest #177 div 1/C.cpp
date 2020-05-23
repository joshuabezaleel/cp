#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
	#define GetTime	printf("Running time: %.3lf second\n",((double)clock())/CLOCKS_PER_SEC);
#else
	#define debug(...) 
	#define GetTime 
#endif

//abbreviations
typedef long long LL;
typedef pair<int,int> PII;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define LLD "%I64d"

//prefefined macros
#define REP(i,n) for (int i = 0; i < n; ++i)
#define REPD(i,n) for (int i = n-1; i >= 0; --i)
#define FOR(i,a,b) for (int i = a; i <= b; ++i)
#define FORD(i,a,b) for (int i = a; i >= b; --i)
#define ALL(a) (a).begin(),(a).end()
#define RESET(a,x) memset(a,x,sizeof(a))
#define EXIST(a,s) ((s).find(a) != (s).end())

/* -------------- end of azaky's template -------------- */

int n,p,t,ans[1111111];

int main(){
	scanf("%d",&n);
	p = n;
	while (p > 0){
		t = 1;
		while (t <= p) t <<= 1;
		t >>= 1;
		FOR(i,t,p){ans[i] = 2*t-1-i; ans[2*t-1-i] = i;}
		p -= 2*(p-t+1);
	}
	LL XOR = 0;
	FOR(i,0,n) XOR += (LL)(i^ans[i]);
	printf("%I64d\n",XOR);
	FOR(i,0,n) printf("%d ",ans[i]); printf("\n");
	
	return 0;
}