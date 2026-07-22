#include <bits/stdc++.h>
using namespace std;
const int MAX_N=5010;

vector<int> grundy(MAX_N);

int gameXOR(string x){
  int xo=0;
  int c=0;
  x+='$';
  int n=x.size();
  for(int i=1;i<n;i++){
    if(x[i-1]==x[i+1]){
      c++;
    } else{
      xo^=grundy[c];
      c=0;
    }
  }
  return xo;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  grundy[0]=0;
  
  for(int L=1;L<MAX_N;L++){
    vector<bool> vis(L+1);
    for(int j=1;j<=L;j++){
      int left=max(0,j-2);
      int right=max(0,L-j-1);

      int game=grundy[left]^grundy[right];
      if(game<=L)
	vis[grundy[left]^grundy[right]]=1;
    }
    int mex=L+1;
    for(int j=0;j<=L;j++){
      if(!vis[j]){
	mex=j;
	break;
      }
    }
    grundy[L]=mex;
  }

  string x; cin>>x;
  int n=x.size();
  if(gameXOR(x)!=0) {
    cout<<"First\n";
    int id=-1;
    for(int i=1;i<n-1;i++){
      if(x[i-1]!=x[i+1]) continue;

      string m1,m2;
      for(int j=0;j<i;j++) m1+=x[j];
      for(int j=i+1;j<n;j++) m2+=x[j];
      
      if((gameXOR(m1) ^ gameXOR(m2))==0){
	id=i;
	break;
      }
    }
    cout<<id+1<<'\n';
  }
  else cout<<"Second\n";
}
