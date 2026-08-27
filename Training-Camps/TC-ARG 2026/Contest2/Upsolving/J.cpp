#include <bits/stdc++.h>
using namespace std;

const int MAX_N=1e6+10;

int n,m;

int freq[MAX_N];

int dp[MAX_N][3][3];

int triple(int id,int prev1, int prev2){
  if(dp[id][prev1][prev2]!=-1) return dp[id][prev1][prev2];
  if(id==m+1) return 0;
  int ans=triple(id+1,0,prev1)+(freq[id]-prev1-prev2)/3;
  for(int i=1;i<=2;i++){
    if(id+2<=m && freq[id+1]-prev1-i>=0 && freq[id+2]-i>=0 && freq[id]-prev1-prev2-i>=0){
      ans=max(ans,triple(id+1,i,prev1)+(freq[id]-prev1-prev2-i)/3+i);
    }
  }
  return dp[id][prev1][prev2]=ans;
}

int main(){
  memset(dp,-1,sizeof dp);
  cin>>n>>m;
  for(int i=0;i<n;i++) {
    int a; cin>>a;
    freq[a]++;
  }
  cout<<triple(1,0,0)<<endl;
}
