#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//bool cmp(A a, A b) { return a.e < b.e; }

int f(vector<pair<int,int>> &v,int ms,int mt) {
	int n=v.size();
    sort(v.begin(), v.end(),[](const pair<int,int>& a,const pair<int,int>& b)
	{if(a.first==b.first) return a.second>b.second;
	else return a.first<b.first;
	});
    int c = 0,s=ms,i=0;
    while(s<mt){
    	int xe=s;
    	while(i<n&&v[i].first<=s){
    		xe=max(xe,v[i].second);
			i++; 
		} 
		if(xe==s){
			return -1;
		}
		s=xe;
		c++;
   	}
    return c;
}

int main() {
	int n,ms,mt;
    cin >> n;
	vector<pair<int,int>> v(n);
    cin>>ms>>mt;

    for (auto& x:v) cin >>x.first>>x.second;
    cout<<"答案是："; 
    cout << f(v,ms,mt) << endl;
}
