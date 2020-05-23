#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
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
	int time_void;
	#define GetTime time_void = clock();\
	printf("Running time: %.3lf second\n",((double)time_void)/CLOCKS_PER_SEC);
#else
	#define debug(...) 
	#define GetTime 
#endif

int getint(){
	int ret = 0, mul = 1;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-'){
		mul = -1;
		ch = getchar();
	}
	do ret = (ret<<1)+(ret<<3)+ch-'0';
	while ((ch = getchar()) && ('0' <= ch && ch <= '9'));
	return ret*mul;
}
void getint(int &x){
	x = getint();
}
long long getLL(){
	long long ret = 0, mul = 1LL;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-'){
		mul = -1LL;
		ch = getchar();
	}
	do ret = (ret<<1)+(ret<<3)+ch-'0';
	while ((ch = getchar()) && ('0' <= ch && ch <= '9'));
	return ret*mul;
}
void getLL(long long &x){
	x = getLL();
}

/* -------------- end of azaky's template -------------- */

const int maxn = 4004;
const int maxx = 1000004;
int n,a[maxn], dp[maxn][maxn], cot[maxx], last[maxx], ans;

int main(){
	for (int i=1; i <= 1000000; ++i) last[i] = -1;
	scanf("%d",&n);
	for (int i=0; i<n; ++i){
		scanf("%d",&a[i]);
		for (int j=0; j<i; ++j){
			if (last[a[i]] > j) dp[i][j] = dp[last[a[i]]][j];
			else if (last[a[i]] == -1) dp[i][j] = 2;
			else if (last[a[i]] < j) dp[i][j] = dp[j][last[a[i]]] + 1;
		}
		last[a[i]] = i;
		cot[a[i]]++;
	}
	ans = 0;
	for (int i=1; i <= 1000000; ++i) if (cot[i] > ans) ans = cot[i];
	for (int i=1; i < n; ++i) for (int j=0; j < i; ++j) if (dp[i][j] > ans) ans = dp[i][j];
	printf("%d\n",ans);
	
	return 0;
}