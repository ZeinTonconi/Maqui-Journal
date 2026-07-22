#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef short shi;

typedef pair<shi,int> si;

#define V vector
#define AR array
#define pb push_back
#define pob pop_back

V<shi> mAux;
V<si> mC;
shi w[12];

V<si> Qs[(1<<12)];
V<si> mQ;

int ans[500000];

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n,m,q; cin>>n>>m>>q;
  for (int i=0; i<n; i++) cin>>w[i];
  for (int i=0; i<m; i++){
    string pat; cin>>pat;
    shi pat_to_int=0;
    for (int j=0; j<n; j++){
      if (pat[j]=='1') pat_to_int|=(1<<j);
    }
    mAux.pb(pat_to_int);
  }

  for (int i=0; i<q; i++){
    string patq; cin>>patq;
    shi k; cin>>k;
    shi patq_to_int=0;
    for (int j=0; j<n; j++){
      if (patq[j]=='1') patq_to_int|=(1<<j);
    }

    Qs[patq_to_int].pb(si(k,i));
  }

  sort(mAux.begin(),mAux.end());

  for (int i=0; i<(int)mAux.size(); i++){
    int j;
    for (j=i; j<(int)mAux.size()&&mAux[i]==mAux[j]; j++) ;
    j--;

    mC.pb(si(mAux[i],j-i+1));

    i=j;
  }

  // now process the queries:

  for (int i=0; i<(1<<n); i++){
    if (Qs[i].empty()) continue;
    sort(Qs[i].begin(), Qs[i].end());
    for (int j=0; j<(int)mC.size(); j++){
      shi acc=0;
      for (int bit=0; bit<n; bit++){
	if ((i&(1<<bit))==(mC[j].first&(1<<bit))){
	  acc+=w[bit];
	}
      }
      mQ.pb(si(acc,mC[j].second));
    }

    sort(mQ.begin(),mQ.end());

    int ptm=0;
    int cnt=0;
    for (int iq=0; iq<(int)Qs[i].size(); iq++){
      while(ptm<(int)mQ.size()&&mQ[ptm].first<=Qs[i][iq].first){
	cnt+=mQ[ptm].second;
	ptm++;
      }
      ans[Qs[i][iq].second]=cnt;
    }
    
    mQ.clear();
  }

  for (int i=0; i<q; i++) cout<<ans[i]<<'\n';

  return 0;
}
