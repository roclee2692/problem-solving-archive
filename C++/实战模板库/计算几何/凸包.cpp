#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const double EPS=1e-9;
//精度处理函数
int sgn(double x){
    if(fabs(x)<EPS) return 0;
    return x<0?-1:1;
}
int dcmp(double x,double y){
    return sgn(x-y);
}

struct Point{
    ll x,y;
    Point(ll x=0,ll y=0):x(x),y(y){}
    Point operator+ (const Point &p) const{
        return Point(x+p.x,y+p.y);
    }
    Point operator- (const Point &p) const{
        return Point(x-p.x,y-p.y);
    }
    Point operator*(ll k) const{
        return Point(x*k,y*k);
    }
    ll cross(const Point &p) const{
        return x*p.y-y*p.x;
    }
    ll dot(const Point &p) const {
        return x*p.x+y*p.y;
    }
    ll len2() const{
        return x*x+y*y;
    }
    double len() const{
        return sqrt(len2());
    }
};

ll cross(const Point &p0,const Point &p1,const Point &p2){
    return (p1-p0).cross(p2-p0);
}

ll dis2(const Point &p1,const Point &p2){
    return (p1-p2).len2();
}
vector<Point> convexHull(vector<Point> points){
    int n=points.size();
    if(n<=2) return points;
    sort(points.begin(),points.end(),[](const Point &a,const Point &b){
        return a.x<b.x || (a.x==b.x && a.y<b.y);
    });
    vector<Point> hull;
    for(int i=0;i)
}