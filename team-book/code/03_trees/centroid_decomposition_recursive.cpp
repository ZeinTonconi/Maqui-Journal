/*
@title: Centroid Decomposition (Recursive)
@complexity: O(n log n)
@tags: trees, centroid decomposition, distance queries
@priority: 20
*/

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecompositionRecursive {
    int n;
    vector<vector<int>> adj;
    vector<int> subtree_size, centroid_parent, centroid_depth;
    vector<char> removed;
    vector<vector<pair<int, int>>> ancestors; // (centroid, distance)

    explicit CentroidDecompositionRecursive(int size)
        : n(size), adj(size), subtree_size(size), centroid_parent(size, -1),
          centroid_depth(size), removed(size, false), ancestors(size) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int calc_size(int v, int p) {
        subtree_size[v] = 1;
        for (int u : adj[v]) {
            if (u == p || removed[u]) continue;
            subtree_size[v] += calc_size(u, v);
        }
        return subtree_size[v];
    }

    int find_centroid(int v, int p, int total) {
        for (int u : adj[v]) {
            if (u == p || removed[u]) continue;
            if (subtree_size[u] > total / 2)
                return find_centroid(u, v, total);
        }
        return v;
    }

    void collect_ancestors(int v, int p, int distance, int centroid) {
        ancestors[v].push_back({centroid, distance});
        for (int u : adj[v]) {
            if (u == p || removed[u]) continue;
            collect_ancestors(u, v, distance + 1, centroid);
        }
    }

    void build_component(int entry, int parent_centroid, int depth) {
        int total = calc_size(entry, -1);
        int centroid = find_centroid(entry, -1, total);
        centroid_parent[centroid] = parent_centroid;
        centroid_depth[centroid] = depth;
        collect_ancestors(centroid, -1, 0, centroid);
        removed[centroid] = true;

        for (int u : adj[centroid]) {
            if (!removed[u])
                build_component(u, centroid, depth + 1);
        }
    }

    void build() {
        if (n > 0) build_component(0, -1, 0);
    }
};
