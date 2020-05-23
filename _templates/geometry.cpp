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

double _acos(double x) {
	double ret = acos(x);
	if (ret == ret) return ret;
	if (x < 0) return acos(-1.0);
	return acos(1.0);
}
#define acos _acos
#define sqr(x) ((x)*(x))

const double PI = acos(-1);
const double EPS = 1e-9;
const double INF = 1e300;

struct point{
	double x, y;
	point() { x = y = 0; }
	point(double x, double y) : x(x), y(y) {}
	point operator-(const point &p) const {
		return point(x - p.x, y - p.y);
	}
	point operator+(const point &p) const {
		return point(x + p.x, y + p.y);
	}
	bool operator<(const point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	double cross(const point &p) {
		return x * p.y - y * p.x;
	}
	double dot(const point &p) {
		return x * p.x + y * p.y;
	}
	double getAngle(const point &p) {
		return fabs(acos(this->dot(p) / this->distance(point(0,0)) / p.distance(point(0,0))));
	}
	double distance(const point &p) const {
		return sqrt(sqr(x - p.x) + sqr(y - p.y));
	}
	double distanceToSegment(const point &p1, const point &p2) {
		double alpha;
		alpha = (p2 - p1).getAngle(*this - p1);
		if (alpha > PI/2 + EPS) return min(this->distance(p1), this->distance(p2));
		alpha = (p1 - p2).getAngle(*this - p2);
		if (alpha > PI/2 + EPS) return min(this->distance(p1), this->distance(p2));
		return fabs((p1 - *this).cross(p2 - *this)) / p1.distance(p2);
	}
	point rotate(const double &alpha) {
		return point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
	}
	point rotate(const double &alpha, const point &center){
		return center + (*this - center).rotate(alpha);
	}
	point rescale(const double s) {
		return point(x * s / this->distance(point(0,0)), y * s / this->distance(point(0,0)));
	}
};
struct circle {
	point center;
	double r;
	circle() { center = point(0, 0); r = 0; }
	circle(point p, double r) : center(p), r(r) {}
};
struct segment {
	point p1, p2;
	segment() {p1 = p2 = point(0,0);}
	segment(point p1, point p2) : p1(p1), p2(p2) {}
	double length(){
		return p1.distance(p2);
	}
};

double distance(point p1,point p2){
	return p1.distance(p2);
}
double distance(point p,segment s){
	return p.distanceToSegment(s.p1,s.p2);
}

double angle(point p1,point o,point p2){
	return (p1-o).getAngle(p2-o);
}
point rotate(point p,point o,double Theta){
	return (p-o).rotate(Theta)+o;
}
point rotate(point p,double Theta){
	return p.rotate(Theta);
}
point dilate(point p,point o,double Factor){
	return (p-o).rescale(Factor)+o;
}
point dilate(point p,double Factor){
	return p.rescale(Factor);
}
double cross(point p1,point p2){
	return p1.cross(p2);
}
bool right(point p1,point p2,point p3){
	return cross(p2-p1,p3-p2)<=0;
}
bool sameside(point p1,point p2,segment s){
	double z1 = cross(s.p2-s.p1,p1-s.p1);
	double z2 = cross(s.p2-s.p1,p2-s.p1);
	return (z1*z2>=0) || fabs(z1)<EPS || fabs(z2)<EPS;
}
bool online(point p,segment s){
	return fabs((s.p1.y-p.y)*(s.p2.x-p.x)-(s.p2.y-p.y)*(s.p1.x-p.x))<EPS;
}
bool onsegment(point p,segment s){
	return fabs(p.distance(s.p1)+p.distance(s.p2)-s.length())<EPS;
}
bool intersect(segment s1,segment s2){
	return !(sameside(s1.p1,s1.p2,s2) || sameside(s2.p1,s2.p2,s1)) || onsegment(s1.p1,s2) || onsegment(s1.p2,s2) || onsegment(s2.p1,s1) || onsegment(s2.p2,s1);
}
bool parallel(segment s1,segment s2){
	return fabs((s1.p1.y-s1.p2.y)*(s2.p1.x-s2.p2.x)-(s2.p1.y-s2.p2.y)*(s1.p1.x-s1.p2.x))<EPS;
}
point intersectpoint(segment s1,segment s2){
	if (parallel(s1,s2)) return point(INF,INF);
    double a1 = s1.p2.x-s1.p1.x;
    double b1 = s2.p1.x-s2.p2.x;
    double c1 = s2.p1.x-s1.p1.x;
    double a2 = s1.p2.y-s1.p1.y;
    double b2 = s2.p1.y-s2.p2.y;
    double c2 = s2.p1.y-s1.p1.y;
    double i = (c1*b2-c2*b1)/(a1*b2-a2*b1);
	return point(s1.p1.x+a1*i,s1.p1.y+a2*i);
}
vector<point> ConvexHull(vector<point> p){
	int n = p.size(), nhull = 2;
	sort(p.begin(),p.end());
	vector<point> hull;
	hull.push_back(p[0]); hull.push_back(p[1]);
	for (int i=2; i<n; ++i){
		while (nhull>1 && right(hull[nhull-2],hull[nhull-1],p[i])){
			--nhull;
			hull.pop_back();
		}
		hull.push_back(p[i]); ++nhull;
	}
	for (int i=n-2; i>=0; --i){
		while (nhull>1 && right(hull[nhull-2],hull[nhull-1],p[i])){
			--nhull;
			hull.pop_back();
		}
		hull.push_back(p[i]); ++nhull;
	}
	hull.pop_back();
	return hull;
}

/* -------------- end of azaky's template -------------- */

const int MAXN = 2222;
int _tc;
int n, r, shot[MAXN], ans, hitall;
point p[MAXN];

bool cmp(const point &a, const point &b){
	return (atan2(a.y,a.x) < atan2(b.y,b.x));
}

bool hit(int i,int k){
	//persamaan garis
	long long a = (long long)p[i].y;
	long long b = -(long long)p[i].x;
	long long lhs = (a*(long long)p[k].x + b*(long long)p[k].y);
	lhs = lhs*lhs;
	long long rhs = (a*a + b*b) * (long long)(r * r);
	return lhs <= rhs;
}

int main(){
	scanf("%d",&_tc);
	for (int tc = 1; tc <= _tc; ++tc){
		scanf("%d%d",&n,&r);
		for (int i=0; i<n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		if (r == 0){
			printf("Case #%d: %d\n",tc,n);
			continue;
		}
		sort(p,p+n,cmp);
		memset(shot,0,sizeof(shot));
		ans = 0;
		for (int i=0; i<n; ++i){
			if (shot[i]) continue;
			hitall = 1;
			for (int j=0; j<i; ++j)
				if (!hit(i,j)){hitall = 0; break;}
			if (hitall) continue;
			++ans;
			for (int j=0; i<n; ++j)
				if (hit(i,j)) shot[j] = 1;
		}
		if (!shot[n-1]) ++ans;
		printf("Case #%d: %d\n",tc,ans);
	}
	return 0;
}