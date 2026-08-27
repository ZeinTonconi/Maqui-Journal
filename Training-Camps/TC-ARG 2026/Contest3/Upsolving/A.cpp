// Inclusion-exclusion
// Separate the counting into two methods, you can't do it all in
// 						       and it will cost you time. Calculate for each path the LCA and process the paths that have the same LCA, and the ones with different, for the first type apply inclusion-exclusion to get all the paths that has more than one vertex rather than the LCA and get the complement, uses the next node in the path (l->u). Then for the second type you have to count the number of paths that includes the actual and the father, so in each end apply +1 and in the LCA -2 then for each path you will need the number of path that includes the grandfather of a node to ignore a branch so apply the same idea, +1 in the end and -1 in the next node in the path (l->u)

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<int,int> ii;

const int MAX_N=3e5+10;

vector<vi> G;
vector<ii> forbid[MAX_N];

int pa[MAX_N][20];
int height[MAX_N];
void preDFS(int u,int p){
  pa[u][0]=p;
  for(int i=1;i<20;i++){
    pa[u][i]=pa[pa[u][i-1]][i-1];
  }
  for(auto &v:G[u]){
    if(v!=p){
      height[v]=height[u]+1;
      preDFS(v,u);
    }
  }
}

int lca(int u,int v){
  if(height[u]<height[v])
    swap(u,v);
  int d=height[u]-height[v];
  for(int i=0;i<20;i++){
    if(d&(1<<i)){
      u=pa[u][i];
    }
  }
  if(u==v) return u;
  for(int i=19;i>=0;i--){
    if(pa[u][i]!=pa[v][i]){
      u=pa[u][i];
      v=pa[v][i];
    }
  }
  return pa[u][0];
}


int getSubtree(int u,int l){
  if(u==l) return -1;
  int h=height[u]-height[l]-1;
  
  for(int i=0;i<20;i++){
    if(h&(1<<i))
      u=pa[u][i];
  }
  return u;
}

int acum[MAX_N];
int acum1[MAX_N];

ll ans=0;

void dfs(int u,int p){
  unordered_map<int,int> oneEnd;
  map<ii,int> twoEnd;
  for(auto &v:forbid[u]){
    oneEnd[v.first]++;
    oneEnd[v.second]++;
    twoEnd[v]++;
  }
  ll comp=0;
  for(auto &v:forbid[u]){
    if(v.first!=-1 && v.second!=-1)
      comp+=oneEnd[v.first]+oneEnd[v.second]-twoEnd[v]-1;
    else if(v.second!=-1)
      comp+=oneEnd[v.second]-1;
  }
  ll t=forbid[u].size();
  ans+=(t*(t-1)/2)-(comp/2);
  
  for(auto &v:G[u]){
    if(v!=p){
      dfs(v,u);
      acum[u]+=acum[v];
      acum1[u]+=acum1[v];
    }
  }

  
  for(auto &v:forbid[u]){
    if(v.first!=-1 && v.second!=-1)
      ans+=(acum[u]-acum1[v.first]-acum1[v.second]);
    else if(v.second!=-1)
      ans+=(acum[u]-acum1[v.second]);
    else
      ans+=acum[u];
  }
}

int main(){
  int n; cin>>n;
  G.resize(n+1);
  for(int i=0;i<n-1;i++){
    int a,b; cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  preDFS(1,1);
  int m; cin>>m;
  for(int i=0;i<m;i++){
    int a,b; cin>>a>>b;
    
    int l=lca(a,b);
    acum[a]++; acum[b]++; acum[l]-=2;
    
    int sub1=getSubtree(a,l),sub2=getSubtree(b,l);
    
    if(sub1!=-1){
      acum1[a]++; acum1[sub1]--;
    }
    if(sub2!=-1){
      acum1[b]++; acum1[sub2]--;
    }
    
    if(sub1>sub2) swap(sub1,sub2);
    ii f=ii(sub1,sub2);
    forbid[l].push_back(f);

  }

  dfs(1,1);

  cout<<ans<<endl;
}
