#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class gh{
    public:
        int v;
        vector<vector<int>> am;
    gh(int v){
        this->v=v;
        am.resize(v,vector<int>(v,INT_MAX));
    }

    void ed(int u,int v,int w){
        am[u][v]=w;
        am[v][u]=w;
    }

    void prim(){
        vector<int> key(v,INT_MAX);
        vector<bool> in(v,false);
        vector<int> pa(v,-1);

        key[0]=0;
        for(int c=0;c<v;c++){
            int u=mk(key,in);
            if (u == -1) break; 
            in[u]=true;
            for(int f=0;f<v;f++){
                if(am[u][f]!=INT_MAX&&!in[f]&&am[u][f]<key[f]){
                    key[f]=am[u][f];
                    pa[f]=u;
                }
            }
        }

       pr(pa);
    }
    private:
        int mk(const vector<int>& key,const vector<bool>& in){
            int min=INT_MAX,mx=-1;
            for(int f=0;f<v;f++){
                if(!in[f]&&key[f]<min){
                    min=key[f];
                    mx=f;
                }
            }
            return mx;
        }
        void pr(const vector<int>& pa){
            cout<<"Edge \t Weight \n";
            for(int i=1;i<v;i++){
                cout<<pa[i]<<"-"<<i<<"\t"<<am[i][pa[i]]<<endl;
            }
        }
};

int main(){
    gh g(5);
    g.ed(0, 1, 2);
    g.ed(0, 3, 6);
    g.ed(1, 2, 3);
    g.ed(1, 3, 8);
    g.ed(1, 4, 5);
    g.ed(2, 4, 7);
    g.ed(3, 4, 9);

    g.prim();  // 执行Prim算法
    return 0;
}