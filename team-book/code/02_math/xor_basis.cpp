/*
@title: XOR Basis
@category: Math
@complexity: O(N log A)
@tags: linear algebra, system of equations
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll rankGauss(vector<ll> x, ll y){
  vector<ll> basis(62,0);
  int r=0;
  int n=x.size();
  for(int i=0;i<n;i++){
    for(int bit=60;bit>=0;bit--){
      if((x[i]>>bit)&1){
        if(!basis[bit]){
          basis[bit]=x[i];
          r++;
          break;
        }
        x[i]^=basis[bit];
      }
    }
  }

  ll ty=y;
  for(int bit=60;bit>=0;bit--){
    if((ty>>bit)&1){
      if(basis[bit]){
	      ty^=basis[bit];
      }
    }
  }
  if(ty!=0) return -1;
  
  // The number of subset that forms y is 2^(n-r) where r is the rank of the basis and n is the number of elements in the original set.

  return r;
}
