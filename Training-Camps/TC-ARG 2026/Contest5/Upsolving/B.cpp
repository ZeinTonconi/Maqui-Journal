#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod=998244353;

ll pot(ll b,ll e){
  if(e==0) return 1;
  if(e==1) return b;
  ll aux=pot(b,e/2);
  aux=(aux*aux)%mod;
  if(e%2!=0) aux=(aux*b)%mod;
  return aux;
}

ll factorial(int n){
  ll p=1;
  for(ll i=1;i<=n;i++){
    p=(p*i)%mod;
  }
  return p;
}

int main(){
  int n,k; cin>>n>>k;
  vector<int> x(n);
  vector<int> pos(n+1);
  for(int i=0;i<n;i++){
    cin>>x[i];
    pos[x[i]]=i;
  }
  pos[n]=-1;
  int c=0;
  for(int i=0;i<n-1;i++){
    if(pos[x[i]+1]>pos[x[i+1]+1])
      c++;
  }

  int t=n+k-c-1;
  if(t<n) cout<<"0\n";
  else{
    ll den=(pot(factorial(n),mod-2)*pot(factorial(t-n),mod-2))%mod;
    ll ans=(factorial(t)*den)%mod;
    cout<<ans<<endl;
  }
  
}
