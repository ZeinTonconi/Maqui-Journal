#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<short,short> ii;
const short MAX_N=3001;
const short MAX=10001;

struct Edge{
  short u,v,w;
  Edge(short u,short v,short w): u(u),v(v),w(w){}
  Edge(){}
};

Edge edge[MAX_N];

struct FlowEdge {
    short v, u;
    short cap, flow = 0;
    FlowEdge(short v, short u, short cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const short flow_inf = MAX_N;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    short s, t;
    vector<short> level, ptr;
    queue<short> q;

    Dinic(short n, short s, short t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(short v, short u, short cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            short v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    int dfs(short v, short pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (short& cid = ptr[v]; cid < adj[v].size(); cid++) {
            int id = adj[v][cid];
            short u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            int tr = dfs(u, min((short)(pushed), (short)(edges[id].cap - edges[id].flow)));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    short flow() {
        short f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (short pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

short restr[MAX_N];
short pa[MAX_N];
short sz[MAX_N];

short ns;
void init(short n){
  for(short i=0;i<=n;i++){
    pa[i]=i;
    sz[i]=1;
  }
  ns=n;
}

short findset(short v){
    while(pa[v]!=v){
        pa[v]=pa[pa[v]];
        v=pa[v];
    }
    return v;
}

bool issameset(short i,short j){
  return findset(i)==findset(j);
}

void unionset(short a, short b){
    a=findset(a);
    b=findset(b);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a,b);
    pa[b]=a;
    sz[a]+=sz[b];
}

short sum[MAX_N];
bool vis[MAX_N];

int rep[MAX_N];
vector<vi> B;

bool check(short k,short n){
  //cout<<k<<endl;
  init(n);
  for(short i=0;i<n-1;i++){
    Edge v=edge[i];
    if(v.w<k) unionset(v.u,v.v);
  }
  
  for(short i=1;i<=n;i++){
    vis[findset(i)]=1;
    sum[findset(i)]+=restr[i];
    sum[findset(i)]=min(sum[findset(i)],n);
  }
  int t=B.size()-1;
  
  Dinic d(2*t+2,0,2*t+1);

  for(short i=1;i<=n;i++){
    if(vis[i]){
      d.add_edge(0,i,sum[i]);
      //cout<<"0 "<<i<<" "<<sum[i]<<endl;
    }
  }

  for(short i=1;i<=n;i++){
    d.add_edge(i+t,2*t+1,1);
    //cout<<i+t<<" "<<2*t+1<<" 1"<<endl;
  }

  for(int i=1;i<=t;i++){
    for(auto &u:B[i]){
      //cout<<i<<" "<<u<<endl;
      d.add_edge(u,i,MAX);
      //cout<<u+t<<" "<<i+t<<endl;
      d.add_edge(i+t,u+t,MAX);
    }
  }
  //cout<<t<<" "<<2*t<<endl;
  d.add_edge(t,2*t,MAX);

  for(short i=1;i<=n;i++) sum[i]=vis[i]=0;
  cout<<"flow "<<k<<": "<<d.flow()<<" "<<n<<endl;
  return d.flow()==n;
}
int newNode=0;

int divide(int l,int r){
  if(l==r)
    return l;
 
  int mid=(l+r)/2;
  int le=divide(l,mid);
  int ri=divide(mid+1,r);
  newNode++;
  B.push_back(vi());
  B[newNode].push_back(le);
  B[newNode].push_back(ri);
  return newNode;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  short n; cin>>n;
  for(short i=0;i<n-1;i++){
    short a,b,w; cin>>a>>b>>w;
    edge[i]=Edge(a,b,w);
  }
  for(short i=1;i<=n;i++) cin>>restr[i];
  newNode=n;
  B.resize(n+1);
  divide(1,n);
  
  short l=0,r=MAX;
  while(r-l>1){
    short mid=(l+r)/2;
    cout<<l<<" "<<r<<" "<<mid<<endl;
    if(check(mid,n))
      l=mid;
    else
      r=mid;
  }
  cout<<l<<'\n';
}
