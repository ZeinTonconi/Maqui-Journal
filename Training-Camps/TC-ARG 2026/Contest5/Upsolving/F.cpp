#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll n,m;

ll expand(ll row,ll col, vector<vi> &diagAsc, vector<vi> &diagDesc, vector<string> &vs){
  bool up=1,down=1,left=1,right=1;

  ll ans=0;
  
  for(ll i=1;i<=max(n,m);i++){
    
    up &= (row-i>0 && vs[row-i][col]=='0');
    
    down &= (row+i<=n && vs[row+i][col]=='0');
    
    left &= (col-i>0 && vs[row][col-i]=='0');
    
    right &= (col+i<=m && vs[row][col+i]=='0');

    ll c0=0,c1=0,c2=0,c3=0;
    bool d1=(row-i>0 && col+i<=m && diagDesc[row][col+i]-diagDesc[row-i-1][col-1]==0);
    bool d0=(col-i>0 && row-i>0 && diagAsc[row-i][col]-diagAsc[row+1][col-i-1]==0);
    bool d2=(col-i>0 && row+i<=n && diagDesc[row+i][col]-diagDesc[row-1][col-i-1]==0);
    bool d3=(row+i<=n && col+i<=m && diagAsc[row][col+i]-diagAsc[row+i+1][col-1]==0);
    
    if(up && right && d1)
      c1=1;
    if(left && up && d0)
      c0=1;
    if(left && down && d2)
      c2=1;
    if(right && down && d3)
      c3=1;
    
    if(left && right && d0 && d1)
      ans++;
    if(up && down && d0 && d2)
      ans++;
    if(left && right && d2 && d3)
      ans++;
    if(up && down && d1 && d3)
      ans++;
    
    ans+=c0+c1+c2+c3;
    //cout<<row<<" "<<col<<": "<<c0<<" "<<c1<<" "<<c2<<" "<<c3<<endl;
    if(up+down+left+right<2) break;
    
  }
  
  return ans;
}

int main(){ cin>>n>>m;
  vector<string> vs;
  vs.push_back("");
  for(ll i=0;i<n;i++){
    string x; cin>>x;
    x="$"+x;
    vs.push_back(x);
  }

  vector<vi> diagAsc(n+2,vi(m+1,0));
  vector<vi> diagDesc(n+1,vi(m+1,0));
  
  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=m;j++){
      diagDesc[i][j]=diagDesc[i-1][j-1]+(vs[i][j]=='1');
    }
  }
  

  for(ll i=n;i>=1;i--){
    for(ll j=1;j<=m;j++){
      diagAsc[i][j]=diagAsc[i+1][j-1]+(vs[i][j]=='1');
    }
  }
  ll ans=0;
  for(ll i=1;i<=n;i++){
    for(ll j=1;j<=m;j++){
      if(vs[i][j]=='0')
	ans+=expand(i,j,diagAsc,diagDesc,vs);
    }
  }

  cout<<ans<<endl;
}
