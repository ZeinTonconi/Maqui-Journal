#include <bits/stdc++.h>
#define ff first
#define sc second


using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin>>n;
  vector<int> v(n);
  for(auto &i:v)cin>>i;
  sort(v.begin(),v.end());

  int sum = 0;
  for(auto i:v)sum+=i;
  int ans = sum;
  for(int i=n-1;i>=1;i--){
    vector<int> div;
    for(int j=2;j<=v[i];j++){
      if(v[i]%j==0){
	div.push_back(j);
      }
    }
    for(auto j:div){
      int cur = sum-v[i];
      cur-=v[0];
      cur+=(v[i]/j);
      cur+=v[0]*j;
      ans=min(ans,cur);
    }
  }
  cout<<ans<<endl;
  
}
