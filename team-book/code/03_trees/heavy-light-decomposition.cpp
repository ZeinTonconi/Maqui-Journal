/*
@title: Heavy Light Decomposition
@category: Trees
@complexity: O(log^2 N)
@tags: HLD, path queries, segment tree
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 5 * 100000 + 1;

int n;
int q;
int h[N];
int sz[N];
int par[N];
int nxt[N];
vector<int> G[N];

void DFS(int u) {
	sz[u] = 1;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		DFS(v);
		sz[u] += sz[v];
		if (sz[v] > sz[G[u][0]]) {
			swap(G[u][i], G[u][0]);
		}
	}
}

void HLD(int u) {
	for (int v : G[u]) {
		h[v] = h[u] + 1;
		par[v] = u;
		nxt[v] = (v == G[u][0] ? nxt[u] : v);
		HLD(v);
	}
}

int lca(int u, int v) {
	while (nxt[u] != nxt[v]) {
		if (h[nxt[u]] > h[nxt[v]]) {
			u = par[nxt[u]];
		}
		else {
			v = par[nxt[v]];
		}
	}
	return h[u] < h[v] ? u : v;
}

int main() {
	cin.tie(0) -> sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		G[p].emplace_back(i);
	}
	DFS(0);
	nxt[0] = 0;
	HLD(0);
	while (q--) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << '\n';
	}
	return 0;
}