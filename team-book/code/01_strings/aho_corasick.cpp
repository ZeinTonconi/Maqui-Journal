/*
@title: Aho-Corasick
@category: Strings
@complexity: O(N+M)
@tags: string matching, trie, aho-corasick
*/

#include <bits/stdc++.h>
using namespace std;

/*
Para frecuencias
template<int E = 26> // E = Alfabeto
struct AhoCorasick {
	int nodes;
	vector<int> suf;
	vector<int> freq;
	vector<int> by_level;
	vector<bool> terminal;
	vector<array<int, E>> go;
	
	AhoCorasick() {
		add_node();
		nodes = 1;
	}
	
	void add_node() {
		terminal.emplace_back();
		suf.emplace_back();
		go.emplace_back();
		freq.emplace_back();
	}
	
	void insert(string &s) {
		int pos = 0;
		for (char ch : s) {
			int c = ch - 'a';
			if (go[pos][c] == 0) {
				go[pos][c] = nodes++;
				add_node();
			}
			pos = go[pos][c];
		}
		terminal[pos] = true;
	}
	
	void build() {
		queue<int> Q;
		Q.emplace(0);
		while (not Q.empty()) {
			int u = Q.front(); Q.pop();
			by_level.emplace_back(u);
			for (int c = 0; c < E; ++c) {
				if (go[u][c]) {
					int v = go[u][c];
					Q.emplace(v);
					suf[v] = u == 0 ? 0 : go[suf[u]][c];
				}
				else {
					go[u][c] = u == 0 ? 0 : go[suf[u]][c];
				}
			}
		}
	}
};*/

// Para existencia
template<int E = 26> // E = Alfabeto
struct AhoCorasick {
	int nodes;
	vector<int> suf;
	vector<int> super;
	vector<bool> terminal;
	vector<array<int, E>> go;
	
	AhoCorasick() {
		add_node();
		nodes = 1;
	}
	
	void add_node() {
		terminal.emplace_back();
		suf.emplace_back();
		go.emplace_back();
		super.emplace_back();
	}
	
	void insert(string &s) {
		int pos = 0;
		for (char ch : s) {
			int c = ch - 'a';
			if (go[pos][c] == 0) {
				go[pos][c] = nodes++;
				add_node();
			}
			pos = go[pos][c];
		}
		terminal[pos] = true;
	}
	
	void build() {
		queue<int> Q;
		Q.emplace(0);
		while (not Q.empty()) {
			int u = Q.front(); Q.pop();
			super[u] = (suf[u] == 0 or terminal[suf[u]] ? suf[u] : super[suf[u]]);
			for (int c = 0; c < E; ++c) {
				if (go[u][c]) {
					int v = go[u][c];
					Q.emplace(v);
					suf[v] = u == 0 ? 0 : go[suf[u]][c];
				}
				else {
					go[u][c] = u == 0 ? 0 : go[suf[u]][c];
				}
			}
		}
	}
};

template<int E = 26>
void mark(int u, AhoCorasick<E> &AC) {
	if (u == 0) return;
	mark(AC.super[u], AC);
	if (AC.terminal[u]) {
		cout << "El nodo " << u << " ocurre como subcadena" << endl;
		AC.terminal[u] = false;
	}
	AC.super[u] = 0;
}

int main() {
	cin.tie(0) -> sync_with_stdio(false);
	AhoCorasick<26> Solver;
	vector<string> S = {"arco", "co", "barco", "oro", "toro"};
	for (string s : S) {
		Solver.insert(s);
	}
	Solver.build();
	const string T = "coroparcotoro";
	int p = 0;
	for (char ch : T) {
		int c = ch - 'a';
		p = Solver.go[p][c];
		mark(p, Solver);
	}
	/*
	for (int i = (int)Solver.by_level.size() - 1; i > 0; --i) {
		int x = Solver.by_level[i];
		Solver.freq[Solver.suf[x]] += Solver.freq[x];
	}
	for (int i = 0; i < Solver.nodes; ++i) {
		cout << "El nodo " << i << " ocurre " << Solver.freq[i] << " veces" << endl;
	}*/
	return 0;
}