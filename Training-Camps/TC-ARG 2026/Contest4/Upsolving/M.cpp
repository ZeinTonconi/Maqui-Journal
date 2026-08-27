#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MAX_N=1010;
const int MAX_M=60;
const int MAX=1e9;

int dp[MAX_N][MAX_M][MAX_M];

vector<int> prefix_function(string &s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

string x,s,t;

vector<int> pis;
vector<int> pit;

vector<vector<int> > forwardS,forwardT;

int solve(int id,int i,int j);

int compare(int i,char c,string &S, vector<int> &pi){
  int newI=i;
  while(newI>0 && c!=S[newI]){
    newI=pi[newI-1];
  }
  if(c==S[newI])
    newI++;

  if(newI==S.size())
    newI=pi[newI-1];
  
  return newI;
}

int forward(int id,int i,int j,char c){

  int score=0;

  if(i==s.size()-1 && s[i]==c)
    score++;

  if(j==t.size()-1 && t[j]==c)
    score--;

  int newI=forwardS[i][c-'a'];

  int newJ=forwardT[j][c-'a'];

  return dp[id+1][newI][newJ]+score;
}

vector<vector<int> > forwardFunction(string &S,vector<int> &pi){

  int n=S.size();

  vector<vector<int> > f(n,vi(26));
  
  for(int i=0;i<S.size();i++){
    for(char j='a';j<='z';j++){
      f[i][j-'a']=compare(i,j,S,pi);
    }
  }
  
  return f;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  memset(dp,-1,sizeof dp);
  
  cin>>x>>s>>t;

  pis=prefix_function(s);
  forwardS=forwardFunction(s,pis);
  
  pit=prefix_function(t);
  forwardT=forwardFunction(t,pit);
  
  for(int i=0;i<s.size();i++){
    for(int j=0;j<t.size();j++) dp[x.size()][i][j]=0;
  }

  for(int id=x.size()-1;id>=0;id--){
    for(int i=0;i<s.size();i++){
      for(int j=0;j<t.size();j++){
	
	int ans=-MAX;

	if(x[id]=='*'){
	  for(char k='a';k<='z';k++){
	    ans=max(ans,forward(id,i,j,k));
	  }
	} else{
	  ans=forward(id,i,j,x[id]);
	}
	dp[id][i][j]=ans;
      }
    }
  }

  cout<<dp[0][0][0]<<"\n";
  
}
