#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//bool cmp(A a, A b) { return a.e < b.e; }

int f(vector<pair<int,int>> &v) {
    sort(v.begin(), v.end(),[](pair<int,int> a,pair<int,int> b){return a.second<b.second;	});
    int c = 0, t = -1;
    for (auto &x : v) {
        if (x.first >= t) { c++; t = x.second; }
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (auto& x:v) cin >>x.first>>x.second;
    cout << f(v) << endl;
}
