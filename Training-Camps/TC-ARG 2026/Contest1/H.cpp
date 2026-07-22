#include <bits/stdc++.h>
using namespace std;

void solve(){
  int n,k; cin>>n>>k;
  vector<int> x(n);
  for(auto &v:x) cin>>v;

  set<int> diff;
  for (int i=0; i<n; i++){
    diff.insert(x[i]);
  }

  if ((int)diff.size()>k){
    cout<<-1<<'\n';
    return;
  }

  int idx_to_pt[k];
  int curridx=0;
  for (auto i=diff.begin(); i!=diff.end(); i++){
    idx_to_pt[curridx]=*i;
    curridx++;
  }
  while(curridx<k){
    idx_to_pt[curridx]=(*diff.begin());
    curridx++;
  }
  int ans[n*k];
  for (int i=0; i<n*k; i++){
    ans[i]=idx_to_pt[i%k];
  }

  cout<<n*k<<'\n';
  for (int i=0; i<n*k; i++) cout<<ans[i]<<' ';
  cout<<'\n';
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  int t; cin>>t;
  while(t--){
    solve();
  }
  
  return 0;
}
