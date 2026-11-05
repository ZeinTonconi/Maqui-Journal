/*
@title: Kruskal Minimum Spanning Tree
@complexity: O(m log m)
@tags: undirected graph, MST, DSU
@priority: 22
*/

#include <bits/stdc++.h>
using namespace std;

struct KruskalMST {
    struct Edge { int u, v; long long w; };
    int n;
    vector<Edge> edges, mst_edges;
    long long total_weight = 0;

    explicit KruskalMST(int size) : n(size) {}

    void add_edge(int u, int v, long long w) {
        edges.push_back({u, v, w});
    }

    pair<bool, long long> build() {
        vector<int> parent(n), size(n, 1);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](int x) {
            int r = x;
            while (r != parent[r]) r = parent[r];
            while (x != r) {
                int p = parent[x];
                parent[x] = r;
                x = p;
            }
            return r;
        };

        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });
        mst_edges.clear();
        total_weight = 0;
        for (const Edge &e : edges) {
            int a = find(e.u), b = find(e.v);
            if (a == b) continue;
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            mst_edges.push_back(e);
            total_weight += e.w;
        }
        return {(int)mst_edges.size() == max(0, n - 1), total_weight};
    }
};
