#include <bits/stdc++.h>
using namespace std;

const int MAX_N=1e5+10;
const int MAX_P=4*MAX_N;
int st[MAX_P];

void init(int node,int a,int b){
  if(a==b){
    st[node]=0;
    return;
  }
  int mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  init(le,a,mid);
  init(ri,mid+1,b);
  st[node]=0;
}

void update(int node,int a,int b,int id,int v){
  if(a==b){
    st[node]=v;
    return;
  }
  int mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  if(id<=mid) update(le,a,mid,id,v);
  else update(ri,mid+1,b,id,v);
  st[node]=max(st[le],st[ri]);
}

int query(int node,int a,int b,int l,int r){
  if(l>r) return 0;
  if(b<l || r<a) return 0;
  if(l<=a && b<=r) return st[node];
  int mid=(a+b)/2,le=2*node+1,ri=2*node+2;
  return max(query(le,a,mid,l,r),query(ri,mid+1,b,l,r));
}


int main(){
  int n; cin>>n;
  vector<int> x(n);
  vector<bool> alive(n);
  for(auto &v:x) cin>>v;
  int ma=0;
  for(int i=0;i<n;i++){
    if(ma<x[i]){
      alive[i]=1;
      ma=x[i];
    }
  }

  vector<int> prev(n,-1);
  stack<int> st;
  for(int i=0;i<n;i++){
    while(!st.empty()){
      int t=st.top();
      if(x[i]<x[t]) break;
      st.pop();
    }
    if(st.empty()) alive[i]=1;
    else prev[i]=st.top();
    st.push(i);
  }
  init(0,0,n-1);
  int ans=0;
  for(int i=1;i<n;i++){
    if(alive[i]) continue;
    
    int q=query(0,0,n-1,prev[i]+1,i);
    q++;
    ans=max(ans,q);
    update(0,0,n-1,i,q);
    // cout<<i<<" "<<q<<endl;
  }
  cout<<ans<<endl;
  
}
