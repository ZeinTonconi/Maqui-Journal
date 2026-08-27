#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;

const ll MAX=1e18;

vector<vector<vector<vector<ll> > > > dp;

ll free(int b,int n,int mask,bool isLead0){
  
  if(dp[b][n][mask][isLead0]!=-1) return dp[b][n][mask][isLead0];
  
  if(n==1 && isLead0)
    return dp[b][n][mask][isLead0]=0;

  if(n==0)
    return dp[b][n][mask][isLead0]=(mask==0);
  
  ll ans=0;
  for(int i=0;i<b;i++){
    if(isLead0){
      int newMask=mask^(1<<i);
      ans+=free(b,n-1,newMask,isLead0)+(newMask==0 && i!=0);
    }
    else
      ans+=free(b,n-1,mask^(1<<i),isLead0);
  }
  
  return dp[b][n][mask][isLead0]=ans;
}

vector<int> decompose(ll x,int b){
  vector<int> d;
  while(x!=0){
    d.push_back(x%b);
    x/=b;
  }
  reverse(d.begin(),d.end());
  return d;
}

ll combi(int n,int c){
  ll prod=1;
  for(ll j=n-c+1;j<=n;j++){
    prod*=j;
  }
  return prod;
}

ll prefix(ll x,int b){
  if(x==0) return 0;
  vector<int> digit=decompose(x,b);

  int t=digit.size();
  ll ans=dp[b][t][0][1];
  int freq=0;
  for(int i=0;i<t;i++){
    int l=(i==0);
    for(int j=l;j<digit[i];j++){
      freq^=(1<<j);
      int c=__builtin_popcount(freq);
      ans+=dp[b][t-i-1][freq][0];
    
      freq^=(1<<j);
    }
    freq^=(1<<digit[i]);
  }
  return ans+(freq==0);
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  dp.resize(11);
  for(int i=2;i<=10;i++){
    vector<int> d=decompose(MAX,i);

    dp[i]=vector<vector<vector<ll>>>(
				      d.size()+1,
				      vector<vector<ll>>(1<<i,
							  vector<ll>(2,-1)));

    for(int j=0;j<=d.size();j++){
      for(int k=0;k<(1<<i);k++){
	for(int l=0;l<2;l++){
	  free(i,j,k,l);
	}
      }
    }
							     
    
  }

  int q; cin>>q;
  while(q--){
    ll b,l,r; cin>>b>>l>>r;
    cout<<prefix(r,b)-prefix(l-1,b)<<endl;;
  }
}
