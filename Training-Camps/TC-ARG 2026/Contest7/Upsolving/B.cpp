#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MAX_N=1e6+10;
const int MAX_B=20;

int pa[MAX_N][MAX_B];

int n,k;

vector<vi> G;

int up[MAX_N];
int ans[MAX_N];

int getFather(int u,int k){
  for(int i=0;i<MAX_B;i++){
    if(k&(1<<i)){
      u=pa[u][i];
    }
  }
  return u;
}

void dfs(int u,int p){
  pa[u][0]=p;
  for(int i=1;i<MAX_B;i++){
    pa[u][i]=pa[pa[u][i-1]][i-1];
  }

  for(auto &v:G[u]){
    if(v!=p){
      dfs(v,u);
    }
  }

  if(G[u].empty()){
    int pk=getFather(u,k);
    ans[pk]++;
    up[pk]--;
    up[u]++;
  }

  if(up[u]){
    ans[p]+=ans[u];
    ans[u]=0;
    up[p]+=up[u];
  }
}

int chooseChild(int u,int p){
  int res=0;
  for(auto &v:G[u]){
    if(v!=p){
      res=max(res,chooseChild(v,u));
    }
  }
  return ans[u]+res;
}

int main(){
  cin>>n>>k;
  G.resize(n+1);
  for(int i=2;i<=n;i++){
    int a; cin>>a;
    G[a].push_back(i);
  }

  dfs(1,1);

  cout<<chooseChild(1,1)<<endl;
}
