#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef long long ll;

vector<vi> G;

struct Query{
  int t,u,type;
};

struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0;
    long long self = 0, path = 0;        // Path aggregates
    long long sub = 0, vir = 0;          // Subtree aggregates
    long long vir2=0;
    bool flip = 0;                       // Lazy tags
  };
  vector<Node> T;
 
  SplayTree(int n) : T(n + 1) {}
  
  void push(int x) {
    if (!x || !T[x].flip) return;
    int l = T[x].ch[0], r = T[x].ch[1];
 
    T[l].flip ^= 1, T[r].flip ^= 1;
    swap(T[x].ch[0], T[x].ch[1]);
    T[x].flip = 0;
  }
  
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r); 
 
    T[x].path = T[l].path + T[x].self + T[r].path;
    T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
  }
  
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x); 
  }
 
  void splay(int x) { 
    auto dir = [&](int x) {
      int p = T[x].p; if (!p) return -1;
      return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) {
      int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, T[x].ch[!dx]); 
      set(x, !dx, y);
      if (~dy) set(z, dy, x); 
      T[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
};

ll s=0;

struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
 
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u); 
      int& ov = T[u].ch[1];
      T[u].vir += T[ov].sub;
      T[u].vir -= T[v].sub;

      T[u].vir2 += T[ov].sub*T[ov].sub;
      T[u].vir2 -= T[v].sub*T[v].sub;
      
      ov = v; pull(u);
    }
    return splay(x), v;
  }
 
  void reroot(int x) { 
    access(x); T[x].flip ^= 1; push(x); 
  }
  
  void Link(int u, int v) { 
    reroot(u); access(v); 
    T[v].vir += T[u].sub;
    T[u].p = v; pull(v);
  }
  
  void Cut(int u, int v) {
    reroot(u); access(v);
    T[v].ch[0] = T[u].p = 0; pull(v);
  }
  
  // Rooted tree LCA. Returns 0 if u and v arent connected.
  int LCA(int u, int v) { 
    if (u == v) return u;
    access(u); int ret = access(v); 
    return T[u].p ? ret : 0;
  }
  
  // Query subtree of u where v is outside the subtree.
  long long Subtree(int u, int v) {
    reroot(v); access(u); return T[u].vir + T[u].self;
  }
  
  // Query path [u..v]
  long long Path(int u, int v) {
    reroot(u); access(v); return T[v].path;
  }
  
  // Update vertex u with value v
  void Update(int u, long long v) {
    access(u); T[u].self = v; pull(u);
  }
};

int main(){
  int n,q; cin>>n>>q;
  vector<int> color(n);
  
  vector<vector<Query> > query(n+1);
  for(int i=0;i<n;i++){
    cin>>color[i];
    
    query[color[i]].push_back({i,i,1});
  }

  LCT lct(n);

  G.resize(n);
  vector<ii> edges;
  for(int i=0;i<n=1;i++){
    int a,b; cin>>a>>b;
    a--; b--;
    if(a>b) swap(a,b);
    G[a].push_back(b);
    G[b].push_back(a);
    
    edges.push_back({a,b});
    
    lct.link(a,b);
  }
  for(int i=0;i<q;i++){
    int u,x; cin>>u>>x;
    u--;

    query[color[u]].push_back({i+n,u,0});
    color[u]=x;
    query[color[u]].push_back({i+n,u,1});
  }

  vector<ll> acumQuery(n+q);

  vector<int> blackWhite(n,1);
  
  for(auto &color:query){
    s=n*n;
    for(int i=0;i<color.size();i++){
      auto &event=color[i];
      if(event.type){
	lct.Update(event.u,0);
	blackWhite[event.u]=0;
	
	cut(event.u);
	// for(auto &v:G[u]){
	//   if(lct.T[event.u].p!=v)
	//     cut(v);
	// }
	
      } else{
	lct.Update(event.u,1);
	blackWhite[event.u]=1;

	link(event.u, lct.T[event.u].p);
	
	// for(auto &v:G[u]){
	//   if(blackWhite[v]){
	//     link(event.u,v);     
	// }
      }

      ll ans=n*n-Subtree(1,1);
      acumQuery[event.t]+=ans;
      if(i+1<color.size())
	acumQuery[color[i+1].t]-=ans;
      
    }

    for(auto &event:color){
      if(!blackWhite[event.u]){
	blackWhite[event.u]=1;
	for(auto &v:G[u]){
	  link(event.u,v);
	}
      }
    }
  }

  ll sum=0;
  for(int i=0;i<acumQuery.size();i++){
    sum+=acumQuery[i];
    if(i>=n-1) cout<<sum<<endl;
  }
  
}
