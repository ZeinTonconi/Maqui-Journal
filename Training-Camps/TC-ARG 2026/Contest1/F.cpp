#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  int t; cin>>t;
  while(t--){
    ll n,g,b; cin>>n>>g>>b;
    ll numG=(n/2)+(n%2!=0);
    ll ans=(numG/g)*b+numG;

    if(numG%g==0){
      ans-=b;
    }
    cout<<max(n,ans)<<'\n';

  }
}
