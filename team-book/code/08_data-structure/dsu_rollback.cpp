/*
@title: DSU with Rollback
@complexity: O(log n) per operation, O(1) per rollback
@tags: DSU, rollback, offline queries
@priority: 30
*/

#include <bits/stdc++.h>
using namespace std;

struct DSURollback {
    int components;
    vector<int> parent, size;
    vector<pair<int, int>> history;

    explicit DSURollback(int n) : components(n), parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) const {
        while (v != parent[v]) v = parent[v];
        return v;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) {
            history.push_back({-1, -1});
            return false;
        }
        if (size[a] < size[b]) swap(a, b);
        history.push_back({b, size[a]});
        parent[b] = a;
        size[a] += size[b];
        --components;
        return true;
    }

    int snapshot() const { return (int)history.size(); }

    void rollback(int snapshot) {
        while ((int)history.size() > snapshot) {
            auto [child, old_size] = history.back();
            history.pop_back();
            if (child == -1) continue;
            int root = parent[child];
            parent[child] = child;
            size[root] = old_size;
            ++components;
        }
    }
};
