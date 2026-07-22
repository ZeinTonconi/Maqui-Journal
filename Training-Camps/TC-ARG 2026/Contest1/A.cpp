#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define V vector
#define pb push_back
#define pob pop_back

const int NAX = 100002;
V<int> listi[NAX]; // reseteado
bool vis[NAX];

void solve(){
  int n; cin>>n;
  for (int i=1; i<=n; i++){
    vis[i]=false; // reseteo el array que uso en el ciclo 2 de mas abajo
    
    listi[i].clear(); // primero reseteo

    // ahora recien meto:
    int k; cin>>k;
    for (int j=0; j<k; j++){
      int elem; cin>>elem;
      listi[i].pb(elem);
    }
  }

  set<int> Ru;
  int iL=-1;
  for (int i=1; i<=n; i++){
    for (int j=0; j<(int)listi[i].size(); j++){
      int elem=listi[i][j];
      if (Ru.find(elem)!=Ru.end()){ // ya se ha usado
	continue;
      }
      vis[i]=true;
      Ru.insert(elem);
      break;
    }

    if (!vis[i]&&iL==-1){
      iL=i;
    }
  }

  if (iL==-1){
    cout<<"OPTIMAL\n";
    return;
  }
  for (int iR=1; iR<=n; iR++){
    if (Ru.find(iR)==Ru.end()){
      cout<<"IMPROVE\n";
      cout<<iL<<' '<<iR<<'\n';
      return;
    }
  }
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int t; cin>>t;
  while(t--) solve();
  
  return 0;
}
