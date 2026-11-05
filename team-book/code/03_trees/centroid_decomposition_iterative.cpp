/*
@title: Centroid Decomposition (Iterative)
@complexity: O(n log n)
@tags: trees, centroid decomposition, distance queries
@priority: 21
*/

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecompositionIterative {
    int n;
    vector<vector<int>> adj;
    vector<int> subtree_size, centroid_parent, centroid_depth;
    vector<char> removed;
    vector<vector<pair<int, int>>> ancestors; // (centroid, distance)

    explicit CentroidDecompositionIterative(int size)
        : n(size), adj(size), subtree_size(size), centroid_parent(size, -1),
          centroid_depth(size), removed(size, false), ancestors(size) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int find_centroid(int entry) {
        vector<int> order, parent(n, -2);
        order.push_back(entry);
        parent[entry] = -1;
        for (int i = 0; i < (int)order.size(); ++i) {
            int v = order[i];
            for (int u : adj[v]) {
                if (removed[u] || u == parent[v]) continue;
                parent[u] = v;
                order.push_back(u);
            }
        }

        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int v = order[i];
            subtree_size[v] = 1;
            for (int u : adj[v])
                if (!removed[u] && parent[u] == v)
                    subtree_size[v] += subtree_size[u];
        }

        int total = (int)order.size();
        for (int v : order) {
            int largest_part = total - subtree_size[v];
            for (int u : adj[v])
                if (!removed[u] && parent[u] == v)
                    largest_part = max(largest_part, subtree_size[u]);
            if (largest_part <= total / 2) return v;
        }
        return entry;
    }

    void collect_ancestors(int centroid) {
        vector<tuple<int, int, int>> st = {{centroid, -1, 0}};
        while (!st.empty()) {
            auto [v, p, d] = st.back();
            st.pop_back();
            ancestors[v].push_back({centroid, d});
            for (int u : adj[v])
                if (!removed[u] && u != p)
                    st.push_back({u, v, d + 1});
        }
    }

    void build() {
        if (n == 0) return;
        vector<tuple<int, int, int>> tasks = {{0, -1, 0}};
        while (!tasks.empty()) {
            auto [entry, parent_centroid, depth] = tasks.back();
            tasks.pop_back();
            if (removed[entry]) continue;

            int centroid = find_centroid(entry);
            centroid_parent[centroid] = parent_centroid;
            centroid_depth[centroid] = depth;
            collect_ancestors(centroid);
            removed[centroid] = true;

            for (int u : adj[centroid])
                if (!removed[u])
                    tasks.push_back({u, centroid, depth + 1});
        }
    }
};
