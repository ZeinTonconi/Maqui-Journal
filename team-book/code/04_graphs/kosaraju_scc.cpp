/*
@title: Strongly Connected Components (Kosaraju)
@complexity: O(n + m)
@tags: directed graph, SCC, condensation graph
@priority: 20
*/

#include <bits/stdc++.h>
using namespace std;

struct KosarajuSCC {
    int n, components = 0;
    vector<vector<int>> g, rg;
    vector<int> order, comp;

    explicit KosarajuSCC(int size) : n(size), g(size), rg(size), comp(size, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    void build() {
        vector<char> seen(n, false);
        order.clear();
        function<void(int)> dfs1 = [&](int v) {
            seen[v] = true;
            for (int u : g[v]) if (!seen[u]) dfs1(u);
            order.push_back(v);
        };
        for (int v = 0; v < n; ++v) if (!seen[v]) dfs1(v);

        fill(comp.begin(), comp.end(), -1);
        components = 0;
        function<void(int)> dfs2 = [&](int v) {
            comp[v] = components;
            for (int u : rg[v]) if (comp[u] == -1) dfs2(u);
        };
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (comp[v] == -1) {
                dfs2(v);
                ++components;
            }
        }
    }

    vector<vector<int>> condensation_graph() const {
        vector<vector<int>> dag(components);
        for (int v = 0; v < n; ++v)
            for (int u : g[v])
                if (comp[v] != comp[u]) dag[comp[v]].push_back(comp[u]);
        for (auto &edges : dag) {
            sort(edges.begin(), edges.end());
            edges.erase(unique(edges.begin(), edges.end()), edges.end());
        }
        return dag;
    }
};
