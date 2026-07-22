#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int main(){
  int n; cin>>n;
  vector<ii> x(n);
  int c=0;
  for(auto &v:x) {
    cin>>v.first;
    v.second=c++;
  }

  vector<ii> ans;
  for(int i=n-1;i>=0;i--){
    vector<ii> inv;

    for(int j=0;j<i;j++){
      if(x[i]<x[j]){
	inv.push_back(ii(j,i));
      }
    }
    
    sort(inv.begin(),inv.end(),[&](ii a,ii b){
      return x[a.first]<x[b.first];
    });

    for(auto &v:inv) {
      ans.push_back(v);
      swap(x[v.first],x[v.second]);
    }
    
  }
  cout<<ans.size()<<endl;
  for(auto &v:ans) cout<<v.first+1<<" "<<v.second+1<<endl;
}
