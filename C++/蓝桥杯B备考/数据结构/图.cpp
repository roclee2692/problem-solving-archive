#include <iostream>
#include <vector>
#include <list>
using namespace std;

class gam{
    public:
        int v;
        vector<vector<int>> adj;
gam(int v){
    this->v=v;
    adj.resize(v,vector<int>(v,0));
}
void addedge(int u,int v){
    adj[u][v]=1;
}
void display(){
    for(int i=0;i<v;++i){
        for(int j=0;j<v;j++){
            cout<<adj[i][j]<<" ";
       }
        cout<<endl;
    }
}

};

class gaj{
    public:
    int v;
    vector<list<int>> adl;

    gaj(int v){
        this->v=v;
        adl.resize(v);
    }
    void addedge(int u,int v){
        adl[u].push_back(v);

    }

    void display(){
        for(int i=0;i<v;i++){
            cout<<"Node "<<i<<":";
            for(auto& a:adl[i]){
                cout<< a <<" ";
            }
            cout<<endl;
        }
    }

};

int main(){
    gam ga(5);
    ga.addedge(0,1);
    ga.addedge(0,2);
    ga.addedge(1,3);
    ga.addedge(2,3); 
    cout<<"Adjacency matrix Representation: "<<endl;
    ga.display();
    
    gaj gs(5);
    gs.addedge(0,1);
    gs.addedge(1,2);
    gs.addedge(1,3);
    gs.addedge(2,3);
    cout<<"\n Adjacency List Representation:"<<endl;
    gs.display();

    return 0;
}