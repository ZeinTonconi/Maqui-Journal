/*
@title: Bridges and Articulation Points
@complexity: O(n + m)
@tags: undirected graph, low-link, bridges, articulation points
@priority: 21
*/

#include <bits/stdc++.h>
using namespace std;

struct BridgesArticulationPoints {
    int n, timer = 0;
    vector<vector<pair<int, int>>> adj; // (neighbor, edge id)
    vector<int> tin, low;
    vector<char> is_bridge, is_articulation;

    explicit BridgesArticulationPoints(int size)
        : n(size), adj(size), tin(size, -1), low(size), is_articulation(size, false) {}

    void add_edge(int u, int v) {
        int id = (int)is_bridge.size();
        is_bridge.push_back(false);
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs(int v, int parent_edge = -1) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [u, id] : adj[v]) {
            if (id == parent_edge) continue;
            if (tin[u] != -1) {
                low[v] = min(low[v], tin[u]);
            } else {
                dfs(u, id);
                low[v] = min(low[v], low[u]);
                if (low[u] > tin[v]) is_bridge[id] = true;
                if (parent_edge != -1 && low[u] >= tin[v])
                    is_articulation[v] = true;
                ++children;
            }
        }
        if (parent_edge == -1 && children > 1) is_articulation[v] = true;
    }

    void build() {
        timer = 0;
        fill(tin.begin(), tin.end(), -1);
        fill(low.begin(), low.end(), 0);
        fill(is_bridge.begin(), is_bridge.end(), false);
        fill(is_articulation.begin(), is_articulation.end(), false);
        for (int v = 0; v < n; ++v)
            if (tin[v] == -1) dfs(v);
    }
};
