#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;

const int MAX_M=1e6+10;
const int MAX_N=1e5+10;

struct Edge{
  int u,v,id;
  Edge(int u,int v,int id):u(u),v(v),id(id){}
};

vector<Edge> edgeW[MAX_M];

int pa[MAX_N];

void init(int n){
  for(int i=0;i<=n;i++)
    pa[i]=i;
}

int findset(int i){
  return (pa[i]==i)?i:pa[i]=findset(pa[i]);
}

bool issameset(int i,int j){
  return findset(i)==findset(j);
}

void unionset(int i,int j){
  if(!issameset(i,j)){
    int u=findset(i);
    int v=findset(j);
    pa[u]=v;
  }
}

int ans[MAX_M];

vector<vii> G;

int timer=0;
int tin[MAX_N],low[MAX_N];
bool vis[MAX_N];

void dfs(int u,int p){
  vis[u]=1;
  tin[u]=low[u]=timer++;
  bool parentSkipped=false;
  for(auto &[v,id]:G[u]){
    if(v==p && !parentSkipped){
      parentSkipped=true;
      continue;
    }
    if(vis[v]){
      low[u]=min(low[u],tin[v]);
    } else{
      dfs(v,u);
      low[u]=min(low[u],low[v]);
      if(low[v]>tin[u]){
	ans[id]=1;
      }
    }
  }
}

void connect(vector<Edge> &edge){
  
  set<int> enable;
  for(auto &e:edge){
    int u=findset(e.u),v=findset(e.v);
    enable.insert(u);
    enable.insert(v);
    
    if(u==v)
      ans[e.id]=2;
    else{
      G[u].push_back(ii(v,e.id));
      G[v].push_back(ii(u,e.id));
    }
  }
  for(auto &e:edge)
    unionset(e.u,e.v);
  
  for(auto &v:enable){
    if(!vis[v]) dfs(v,v);
  }
  timer=0;
  for(auto &v:enable){
    G[v].clear();
    vis[v]=0;
  }
}

int main(){
  int n,m; cin>>n>>m;
  G.resize(n+1);
  for(int i=0;i<m;i++){
    int a,b,w; cin>>a>>b>>w;
    edgeW[w].push_back(Edge(a,b,i));
  }

  init(n);
  for(int i=1;i<MAX_M;i++){
    connect(edgeW[i]);
  }
  for(int i=0;i<m;i++){
    if(ans[i]==1) cout<<"any\n";
    if(ans[i]==0) cout<<"at least one\n";
    if(ans[i]==2) cout<<"none\n";
  }
}
