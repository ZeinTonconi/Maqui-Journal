#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define V vector
#define pb push_back
#define pob pop_back

int a[3][6];
int n;

int msk;
V<int> L;
set<int> nums;
void gen(int rwpos){
  if (rwpos==n){
    if (L.empty()) return;
    V<int> newl=L;
    sort(newl.begin(),newl.end());
    do{
      if (!newl.front()) continue;
      int curr=0;
      for (int I=0; I<(int)newl.size(); I++){
	curr*=10;
	curr+=newl[I];
      }
      nums.insert(curr);
    }while(next_permutation(newl.begin(),newl.end()));
    
    return;
  }

  if (!(msk&(1<<rwpos))) gen(rwpos+1);
  for (int i=0; i<6; i++){
    L.pb(a[rwpos][i]);
    gen(rwpos+1);
    L.pob();
  }
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin>>n;

  for (int i=0; i<n; i++){
    for (int j=0; j<6; j++) cin>>a[i][j];
  }
  
  for (msk=0; msk<(1<<n); msk++){
    gen(0);
  }

  int ans=0;
  for (int x=1; true; x++){
    if (nums.find(x)!=nums.end()){
      ans=x;
    }else break;
  }
  cout<<ans<<'\n';

  return 0;
}
