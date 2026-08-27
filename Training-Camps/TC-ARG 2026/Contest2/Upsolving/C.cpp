#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

const ll MAX_N=5e5+10;
const ll MAX=1e18;

vector<vi> G;

ll weight[MAX_N];

struct Query{
  ll l,r,id;
  Query(){}
  Query(ll _l,ll _r,ll _id):l(_l),r(_r),id(_id){}
};

ll dis[MAX_N];

vector<ll> childId;
ii range[MAX_N];

void dfs(ll u){
  
  range[u]=ii(MAX,-MAX);

  if(G[u].empty()) range[u]=ii(childId[u],childId[u]);

  for(auto &v:G[u]){
    dis[v]=dis[u]+weight[v];
    dfs(v);
    range[u].first=min(range[u].first,range[v].first);
    range[u].second=max(range[u].second,range[v].second);
  }
}
const int MAX_P=4*MAX_N;
ll st[MAX_P];
ll la[MAX_P];

vector<ll> child;
  
void init(ll node,ll a,ll b){
  if(a==b){
    //cout<<node<<" "<<a<<" "<<b<<" "<<dis[child[a]]<<" "<<child[a]<<endl;
    st[node]=dis[child[a]];
    la[node]=0;
    return;
  }
  ll mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  init(le,a,mid);
  init(ri,mid+1,b);
  st[node]=min(st[le],st[ri]);
  la[node]=0;
}

void push(ll node, ll a,ll b){
  if(a==b) return;
  ll le=2*node+1;
  ll ri=2*node+2;
  st[le]+=la[node];
  st[ri]+=la[node];
  la[le]+=la[node];
  la[ri]+=la[node];
  
  la[node]=0;
  return;
}

void update(ll node,ll a,ll b,ll l,ll r,ll v){
  if(b<l || r<a) return;
  push(node,a,b);
  if(l<=a && b<=r){
    st[node]+=v;
    la[node]=v;
    return;
  }
  
  ll mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  update(le,a,mid,l,r,v);
  update(ri,mid+1,b,l,r,v);

  st[node]=min(st[le],st[ri]);
}

ll query(ll node,ll a,ll b,ll l,ll r){
  if(b<l || r<a) return MAX;
  push(node,a,b);
  if(l<=a && b<=r)
    return st[node];
  ll mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  return min(query(le,a,mid,l,r),query(ri,mid+1,b,l,r));
}

ll n;

void process(ll u,vector<vector<Query> > &q,vector<ll> &ans,ll numChild){

  //cout<<u<<": \n";
  
  for(auto &v:q[u]){
    auto left=lower_bound(child.begin(),child.end(),v.l);
    auto right=upper_bound(child.begin(),child.end(),v.r);
    right--;
    ll l=childId[child[left-child.begin()]];
    ll r=childId[child[right-child.begin()]];
  
    ll q=query(0,0,numChild,l,r);
    ans[v.id]=q;
    
  }

  
  for(auto &v:G[u]){
    //cout<<range[v].first<<" "<<range[v].second<<endl;
    update(0,0,numChild,range[v].first,range[v].second,-2LL*weight[v]);
    update(0,0,numChild,0,numChild,weight[v]);
    
    process(v,q,ans,numChild);
    //cout<<range[v].first<<" "<<range[v].second<<endl;
    update(0,0,numChild,range[v].first,range[v].second,2LL*weight[v]);
    update(0,0,numChild,0,numChild,-weight[v]);
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ll q; cin>>n>>q;

  G.resize(n+1);
  for(ll i=2;i<=n;i++){
    ll a,w; cin>>a>>w;
    G[a].push_back(i);
    weight[i]=w;
  }
  
  for(ll i=1;i<=n;i++){
    if(G[i].empty()){
      child.push_back(i);
    }
  }

  childId.resize(n+1,-1);
  for(ll i=0;i<child.size();i++){
    childId[child[i]]=i;
  }
  
  vector<vector<Query> > query(n+1);

  vector<ll> ans(q); 

  for(ll i=0;i<q;i++){
    ll v,l,r; cin>>v>>l>>r;
    query[v].push_back(Query(l,r,i));
  }

  dis[1]=0;
  dfs(1);

  /*for(auto &v:child) cout<<v<<" ";
  cout<<endl;
  for(auto &v:childId) cout<<v<<" ";
  cout<<endl;
  for(ll i=1;i<=n;i++){
    cout<<range[i].first<<" "<<range[i].second<<endl;
  }*/
  
  ll numChild=child.size()-1;
  init(0,0,numChild);

  process(1,query,ans,numChild);

  for(auto &v:ans) cout<<v<<endl;
    
}
