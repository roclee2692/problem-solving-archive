#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int n;
vector<int> res;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    vector<int> left(n, -1);
    vector<int> right(n, -1);
    vector<bool> is_child(n, false);

    for(int i=0;i<n;i++){
        string l,r;//这里是字符串类型 下面的比较都要用字符串类型
        cin>>l>>r;
        if(l!="-"){
            left[i]=stoi(l);
            is_child[left[i]]=1;
        }
        if(r!="-"){
            right[i]=stoi(r);
            is_child[right[i]]=1;//这里索引必须为同类型数据
        }
    }

    int root=-1;
    for(int i=0;i<n;i++){
        if(!is_child[i]){
            root=i;
            break;
        }
    }
    queue<int> q;
    q.push(root);

    while(!q.empty()){
        int node=q.front();
        q.pop();

        if(left[node]==-1&&right[node]==-1){
            res.push_back(node);
        }
        else{//这里的括号是{} 不是（）
            if(left[node]!=-1) q.push(left[node]);
            if(right[node]!=-1) q.push(right[node]);
        }
    }
for(size_t i=0;i<res.size();i++){
    if(i) cout<<" ";
    cout<<res[i];
}
cout<<endl;
  return 0;
}