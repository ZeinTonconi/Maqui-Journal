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
  int lf[n+1];
  int rh[n+1];
  int cnt0 = 0;
  vector<int> rh0;
  for(int i=1;i<=n;i++){
    cin>>lf[i]>>rh[i];
    if(rh[i]==0)rh0.push_back(i);
  }
  cnt0 = rh0.size();
  vector<vector<int>> lis(cnt0+1,vector<int>());
  for(int i=0;i<cnt0;i++){
    lis[i].push_back(rh0[i]);
    int val = rh0[i];
    while(lf[val]!=0){
      lis[i].push_back(lf[val]);
      val = lf[val];
    }
  }
  for(int i=0;i<cnt0;i++){
    int llf = lis[i].back();
    if(i==cnt0-1)continue;
    int rrh = lis[i+1][0];
    //    cout<<llf<<" "<<rrh<<endl; 
    lf[llf]=rrh;
    rh[rrh]=llf;
  }
  for(int i=1;i<=n;i++){
    cout<<lf[i]<<" "<<rh[i]<<endl;
  }
}
