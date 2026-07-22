#include <bits/stdc++.h>
#define ff first
#define sc second


using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

bool fun(string s,int t,set<int> ps){
  set<int> rs;
  // cout<<t<<endl;
  for(int i=0;i<s.size();i++){
    if(s[i]=='*'){
      if(rs.lower_bound(i)!=rs.end()){
	continue;
      }
      auto it = ps.upper_bound(i);
      if(it==ps.end()){
	return false;
      }
      int piv = *it;      
      int dis = piv - i;
      if(t<dis)return false;
      int newp =max(max(piv,piv+(t-2*(dis))),piv+((t-dis)/2));
      //int newp = max(piv,piv+(t-2*(dis)));
      rs.insert(newp);
      s[piv]='.';
      ps.erase(it);
    }
    if(s[i]=='P'){
      rs.insert(i+t);
    }
  }
  // cout<<"Si"<<endl;
  return true;
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin>>n;
  string s;
  cin>>s;
  set<int> ps;
  int j =0;
  for(auto i:s){
    if(i=='P')ps.insert(j);
    j++;
  }
  int lo = 0,hi=1e9;
  while(hi-lo>1){
    int mid = (lo+hi)/2;
    if(fun(s,mid,ps)){
      hi=mid;
    }
    else lo=mid;
  }
  cout<<hi<<endl;
}



