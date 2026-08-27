#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAX=1e9;
const int MAX_N=1501;

int n,m; 
vector<string> vs;

ii reach[MAX_N][MAX_N];

int X[5]={-1,0,1,0};
int Y[5]={0,1,0,-1};
bool ans=0;
void hasCycle(int x,int y){

  reach[(x%n+n)%n][(y%m+m)%m]=ii(x,y);
  
  for(int i=0;i<4;i++){
    int xk=x+X[i];
    int yk=y+Y[i];
    
    if(vs[(xk%n+n)%n][(yk%m+m)%m]=='#') continue;
    
    if(reach[(xk%n+n)%n][(yk%m+m)%m]==ii(-MAX,-MAX)){
      hasCycle(xk,yk);
      if(ans)
	return;
    }
    else{
      if(reach[(xk%n+n)%n][(yk%m+m)%m]!=ii(xk,yk)){
	ans=1;
	return;
      }
    }
  }
  return;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin>>n>>m;

  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++) reach[i][j]=ii(-MAX,-MAX);
  }
  
  vs.resize(n);
  for(auto &v:vs) cin>>v;

  int xs,ys;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(vs[i][j]=='S'){
	xs=i;
	ys=j;
      }
    }
  }
  hasCycle(xs,ys);
  cout<<(ans?"Yes\n":"No\n");
  
}
