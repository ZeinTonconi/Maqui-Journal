#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
const int MAX_N=65;
const int MAX_M=257;

typedef vector<int> vi;

int color[MAX_M];
int G[MAX_N][MAX_N];

struct Triangle{
  int a,b,c;
  Triangle(){}
  Triangle(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
};

const int INF = 2;
const int mod = 3;

const int mul[3][3] = {
    {0, 0, 0},
    {0, 1, 2},
    {0, 2, 1}
};

const int sub[3][3] = {
    {0, 2, 1},
    {1, 0, 2},
    {2, 1, 0}
};

int gauss(vector<vector<int>> &a, vector<int> &ans) {
    int n = a.size();
    int m = a[0].size() - 1;

    vector<int> where(m, -1);

    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++) {
            if (a[i][col]) {
                sel = i;
                break;
            }
        }

        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;

        int invPivot = a[row][col]; 
        for (int i = 0; i < n; i++) {
            if (i == row) continue;
            if (a[i][col] == 0) continue;

            int factor = mul[a[i][col]][invPivot];

            for (int j = col; j <= m; j++)
                a[i][j] = sub[a[i][j]][mul[factor][a[row][j]]];
        }

        row++;
    }

    ans.assign(m, 0);

    for (int i = 0; i < m; i++)
        if (where[i] != -1)
            ans[i] = mul[a[where[i]][m]][a[where[i]][i]];

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += mul[ans[j]][a[i][j]];
            if (sum >= 3) sum -= 3;
            if (sum >= 3) sum -= 3;
        }

        if (sum != a[i][m])
            return 0;
    }

    for (int i = 0; i < m; i++)
        if (where[i] == -1)
            return INF;

    return 1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    memset(G,-1,sizeof G);

    for(int i=0;i<m;i++){
      int a,b,c; cin>>a>>b>>c;
      c--;
      c=max(-1,c);
      G[a][b]=G[b][a]=i;
      color[i]=c;
    }

    vector<Triangle> tri;
    
    for(int i=1;i<=n;i++){
      for(int j=i+1;j<=n;j++){
	for(int k=j+1;k<=n;k++){
	  if(G[i][j]!=-1 && G[i][k]!=-1 && G[j][k]!=-1){
	    tri.push_back(Triangle(G[i][j],G[i][k],G[j][k]));
	  }
	}
      }
    }

    vector<vector<int> > A;
    for(int i=0;i<tri.size();i++){
      vector<int> eq(m+1,0);
      auto [x0,x1,x2]=tri[i];
      int b=0;
      if(color[x0]!=-1)
	b=(b-color[x0]+mod)%mod;
      else
	eq[x0]=1;
      
      if(color[x1]!=-1)
	b=(b-color[x1]+mod)%mod;
      else
	eq[x1]=1;
      
      if(color[x2]!=-1)
	b=(b-color[x2]+mod)%mod;
      else
	eq[x2]=1;

      eq[m]=b;
      bool ok=0;
      for(auto &v:eq){
	if(v!=0) ok=1;
      }
      if(ok)
	A.push_back(eq);
    }
    
    if(A.empty()){
      for(int i=0;i<m;i++){
	if(color[i]==-1) color[i]=0;
	color[i]++;
	cout<<color[i]<<" ";
      }
      cout<<'\n';
      continue;
    }
    vector<int> ans;
    int g=gauss(A,ans);
    if(g==0) cout<<"-1\n";
    else{
      for(int i=0;i<m;i++){
	if(color[i]==-1) color[i]=ans[i];
	color[i]++;
      }

      bool ok=1;
      for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++){
	  for(int k=j+1;k<=n;k++){
	    if(G[i][j]==-1 || G[i][k]==-1 || G[j][k]==-1) continue;
	    int c1=color[G[i][j]];
	    int c2=color[G[i][k]];
	    int c3=color[G[j][k]];
	    if(!((c1==c2 && c2==c3) || (c1!=c2 && c2!=c3)))
	      ok=0;
	    
	  }
	}
      }
      if(ok){
	for(int i=0;i<m;i++)
	  cout<<color[i]<<" ";
	cout<<'\n';
      } else cout<<"-1\n";
    }
  }
}
