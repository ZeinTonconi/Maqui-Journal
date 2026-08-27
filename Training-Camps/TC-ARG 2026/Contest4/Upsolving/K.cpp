#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int MAX_M=2e5+10;
const int SQRT_MAX=500;

int acum[MAX_M];

int start[MAX_M];

vector<vector<int> > small(SQRT_MAX);

int n,m;

void bigRange(int s,int x,int y,int v){
  int e=s;
  while(e<=m){
    if(e+x<=m)
      acum[e+x]+=v;
    if(e+x+y<=m)
      acum[e+x+y]-=v;
    e+=x+y;
  }
}

void smallRange(int s,int x,int y,int v){

  int a=x+y;
  int e=(s+x)%a;
  for(int i=0;i<y;i++){
    small[a][e]+=v;
    e=(e+1)%a;
  }
  
}

void resetAns(int s,int x,int y,int e,int &ans){
  while(s<e){
    if(s+x<e) ans--;
    if(s+x+y<e) ans++;
    s+=x+y;
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin>>n>>m;
  vector<ii> x(n);
  for(auto &v:x)
    cin>>v.first>>v.second;

  memset(start,0,sizeof start);

  for(int i=0;i<SQRT_MAX;i++){
    small[i].resize(i);
  }
  
  int ans=0;
  
  for(int i=1;i<=m;i++){
    int op,a;
    cin>>op>>a; a--;
    int v,s;
    if(op==2){
      s=start[a];
      start[a]=-1;
      v=-1;
      
    }
    else{
      s=i;
      start[a]=i;
      v=1;
    }

    if(x[a].first+x[a].second>=SQRT_MAX){
      if(op==2)
	resetAns(s,x[a].first,x[a].second,i,ans);
      
      bigRange(s,x[a].first,x[a].second,v);
    }
    else{
      smallRange(s,x[a].first,x[a].second,v);
    }

    ans+=acum[i];
    int pa=ans;
    for(int j=1;j<SQRT_MAX;j++)
      pa+=small[j][i%j];

    cout<<pa<<'\n';
    
  }
  
}
