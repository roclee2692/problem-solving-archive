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

// 整型坐标版本（精确，用于整数点）
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

// 浮点坐标版本（用于浮点数点，需要精度处理）
struct PointD{
    double x,y;
    PointD(double x=0,double y=0):x(x),y(y){}
    PointD operator+ (const PointD &p) const{
        return PointD(x+p.x,y+p.y);
    }
    PointD operator- (const PointD &p) const{
        return PointD(x-p.x,y-p.y);
    }
    PointD operator*(double k) const{
        return PointD(x*k,y*k);
    }
    double cross(const PointD &p) const{
        return x*p.y-y*p.x;
    }
    double dot(const PointD &p) const {
        return x*p.x+y*p.y;
    }
    double len2() const{
        return x*x+y*y;
    }
    double len() const{
        return sqrt(len2());
    }
    bool operator<(const PointD &p) const{
        return dcmp(x,p.x)<0 || (dcmp(x,p.x)==0 && dcmp(y,p.y)<0);
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
    for(int i=0;i<n;i++){
        while(hull.size()>=2 && 
        cross(hull[hull.size()-2],hull[hull.size()-1],points[i])<=0){
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    int lower_size=hull.size();
    for(int i=n-2;i>=0;i--){
        while(hull.size()>lower_size &&
        cross(hull[hull.size()-2],hull[hull.size()-1],points[i])<=0){
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}
double perimeter(const vector<Point> &hull){
    double per=0;
    int n=hull.size();
    for(int i=0;i<n;i++){
        per+=(hull[(i+1)%n]-hull[i]).len();
    }
    return per;
}
double area(const vector<Point> &hull){
    ll a=0;
    int n=hull.size();
    for(int i=0;i<n;i++){
        a+=hull[i].cross(hull[(i+1)%n]);
    }
    return abs(a)/2.0;
}
ll rotatingCalipers(const vector<Point> &hull){
    int n=hull.size();
    if(n<=2) return dis2(hull[0],hull[n-1]);
    ll max_dis=0;
    int j=1;
    for(int i=0;i<n;i++){
        while(1){
            ll c1=cross(hull[i],hull[(i+1)%n],hull[j]);
            ll c2=cross(hull[i],hull[(i+1)%n],hull[(j+1)%n]);
            if(c2>c1){
                j=(j+1)%n;
            }else break;
        }
        max_dis=max(max_dis,dis2(hull[i],hull[j]));
        max_dis=max(max_dis,dis2(hull[(i+1)%n],hull[j]));
    }
    return max_dis;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<Point> points(n);
    for(int i=0;i<n;i++){
        cin>>points[i].x>>points[i].y;
    }
    vector<Point> hull=convexHull(points);
    cout<<fixed<<setprecision(2)<<perimeter(hull)<<"\n";
    return 0;
}