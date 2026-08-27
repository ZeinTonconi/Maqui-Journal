#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;

const int MAX_N=3e5+10;

vector<vi> G;

ii dp[MAX_N][2];

int dfs(int u,int p){
  vector<ii> ansCh;
  for(auto &v:G[u]){
    if(v!=p)
      ansCh.push_back(ii(dfs(v,u)-1,v));
  }
  sort(ansCh.begin(),ansCh.end());
  reverse(ansCh.begin(),ansCh.end());
  
  if(ansCh.size()>0){
    dp[u][0]=ansCh[0];
    dp[u][0].first+=(u==p);
  }
  if(ansCh.size()>1){
    dp[u][1]=ansCh[1];
    dp[u][1].first+=(u==p);
      
  }
  
  dp[u][1].first+=G[u].size();
  dp[u][0].first+=G[u].size();
  
  return dp[u][0].first;
}

int ans=0;
void rerooting(int u,int p){
  ans=max(ans,dp[u][0].first);
  for(auto &v:G[u]){
    if(v!=p){
      ii prevV=dp[v][0], prevU=dp[u][1];
      int take=0;
      if(v==dp[u][0].second){
	take=1;
      }
      
      if(dp[v][0].first<dp[u][take].first+G[v].size()-1){
	dp[v][0]=ii(dp[u][take].first+G[v].size()-1,u);
      } else{
	dp[v][0].first++;
      }
      
      rerooting(v,u);
      
      dp[v][0]=prevV;
      
    }
  }
}


int main(){
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    G.clear(); G.resize(n+1);
    for(int i=0;i<=n;i++){
      for(int j=0;j<2;j++) dp[i][j]=ii(0,0);
    }
    for(int i=0;i<n-1;i++){
      int a,b; cin>>a>>b;
      G[a].push_back(b);
      G[b].push_back(a);
    }
    dfs(1,1);
     // for(int i=1;i<=n;i++) cout<<i<<": "<<dp[i][0].first<<" "<<dp[i][0].second<<", "<<dp[i][1].first<<" "<<dp[i][1].second<<endl;
    ans=0;
    rerooting(1,1);
    cout<<ans<<endl;
  }
}
