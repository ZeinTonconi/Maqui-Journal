#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canmove(ll x, ll y, ll k, ll d, bool turn){
  if (!turn) x+=k;
  else y+=k;
  return (x*x + y*y <= d*d);
}

void solve(){
  ll d; cin>>d;
  ll k; cin>>k;
  int x=0, y=0;
  bool turn=0;
  while(canmove(x,y,k,d,turn)){
    if (!turn){
      x+=k;
    }else{
      y+=k;
    }
    turn^=1;
  }
  turn^=1;
  if (!turn) cout<<"Ashish\n";
  else cout<<"Utkarsh\n";
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int t; cin>>t;
  while(t--) solve();

  return 0;
}
