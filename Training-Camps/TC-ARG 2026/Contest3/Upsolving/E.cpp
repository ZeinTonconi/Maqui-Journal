#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ii> vi;

const ll MAX=1e18;
const int MAX_N=2010;

bool path[MAX_N];

vector<vi> G;

int bfs(int s,vector<ll> &dis,int n){

  vector<bool> vis(n+1);
  
  dis.assign(n+1,MAX);
  queue<int> q;
  dis[s]=0;
  vis[s]=1;
  q.push(s);
  while(!q.empty()){
    int u=q.front();
    q.pop();
    for(auto &v:G[u]){
      if(!path[v.first] && dis[v.first]>dis[u]+v.second){
	dis[v.first]=dis[u]+v.second;
	q.push(v.first);
	vis[v.first]=1;
      }
    }
  }
  ll ma=dis[s];
  int id=s;
  for(int i=1;i<=n;i++){
    if(ma<dis[i] && vis[i]){
      ma=dis[i];
      id=i;
    }
  }
  return id;
}

bool mark(int s,int p,int e){
  if(s==e)
    return path[s]=1;
  
  for(auto &v:G[s]){
    if(v.first!=p && !path[v.first]){
      if(mark(v.first,s,e))
	return path[s]=1;
    }
  }
  return 0;
}

ii diameter(int s,int n, bool isMark=1){

  vector<ll> dis;
  s=bfs(s,dis,n);
  int e=bfs(s,dis,n);

 
  if(isMark)
    mark(s,s,e);

  
  return ii(dis[e],e);
  
}

int main(){
  memset(path,0,sizeof path);
  int n,k; cin>>n>>k;
  G.assign(n+1,vi());
  for(int i=0;i<n-1;i++){
    int a,b,w; cin>>a>>b>>w;
    G[a].push_back(ii(b,w));
    G[b].push_back(ii(a,w));
  }
  
  auto [dim,e]=diameter(1,n,1);

  cout<<dim<<" ";

  ll ans=dim;
  for(int i=0;i<k;i++){
    int si,ei;
    ll maxDiam=-1;
    for(int j=1;j<=n;j++){
      if(path[j]){
	for(auto &v:G[j]){
	  if(!path[v.first]){  
	    auto [diam,e]=diameter(v.first,n,0);
	    diam+=v.second;
	    if(maxDiam<diam){
	      maxDiam=diam;
	      si=v.first; ei=e;
	    }
	  }
	}
      }
    }
    mark(si,si,ei);
    ans+=maxDiam;
    cout<<ans<<" ";
  }
  cout<<endl;
  
  
  
}
