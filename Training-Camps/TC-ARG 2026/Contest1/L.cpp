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
  ll cnta0 = 0;
  ll cntb0 = 0;
  map<ii,int> mp;
  map<ii,int> inv;

  vector<int> a(n);
  vector<int> b(n);
  for(auto &i:a)cin>>i;
  for(auto &i:b)cin>>i;

  for(int i=0;i<n;i++){
    while(__gcd(abs(a[i]),abs(b[i]))!=1 && a[i]!=0 && b[i]!=0){
      ll aux =abs(__gcd(a[i],b[i]));
      a[i]/=aux;
      b[i]/=aux;
    }
    if(a[i]!=0 && b[i]!=0){
      mp[ii(a[i],b[i])]++;
      inv[ii(-a[i],-b[i])]++;
    }
    else if(a[i]==0){
      if(b[i]==0)cnta0++;     
    }
    else if(b[i]==0){
      cntb0++;
    }
  }
  ll ans=max(cnta0,cntb0+cnta0);
  ll cur = 0;
  for(auto it = mp.begin();it!=mp.end();it++){
    ll x = (*it).ff.ff;
    ll y = (*it).ff.sc;
    cur=max(cur,mp[ii(x,y)]+inv[ii(x,y)]+cnta0);
  }
  ans=max(ans,cur);
  cout<<ans<<endl;
  
}
