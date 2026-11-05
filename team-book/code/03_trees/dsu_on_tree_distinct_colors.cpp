/*
@title: DSU on Tree (Distinct Colors in Subtree)
@complexity: O(n log n)
@tags: trees, sack, subtree queries
@priority: 33
*/

#include <bits/stdc++.h>
using namespace std;

// Returns the number of distinct color values in each rooted subtree (root 0).
vector<int> distinct_colors_in_subtrees(
    const vector<vector<int>> &tree,
    const vector<int> &color
) {
    int n = (int)tree.size();
    vector<int> parent(n, -1), size(n, 1), heavy(n, -1), order;
    vector<int> answer(n), compressed = color;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());
    vector<int> id(n);
    for (int v = 0; v < n; ++v)
        id[v] = lower_bound(compressed.begin(), compressed.end(), color[v]) - compressed.begin();
    if (n == 0) return answer;

    order.push_back(0);
    for (int i = 0; i < (int)order.size(); ++i) {
        int v = order[i];
        for (int u : tree[v]) if (u != parent[v]) {
            parent[u] = v;
            order.push_back(u);
        }
    }
    for (int i = n - 1; i > 0; --i) {
        int v = order[i], p = parent[v];
        size[p] += size[v];
        if (heavy[p] == -1 || size[v] > size[heavy[p]]) heavy[p] = v;
    }

    vector<int> freq(compressed.size());
    int distinct = 0;
    auto add_subtree = [&](int start, int delta) {
        vector<pair<int, int>> st = {{start, parent[start]}};
        while (!st.empty()) {
            auto [v, p] = st.back(); st.pop_back();
            if (delta == 1) distinct += (freq[id[v]]++ == 0);
            else distinct -= (--freq[id[v]] == 0);
            for (int u : tree[v]) if (u != p) st.push_back({u, v});
        }
    };
    function<void(int, bool)> solve = [&](int v, bool keep) {
        for (int u : tree[v]) if (parent[u] == v && u != heavy[v]) solve(u, false);
        if (heavy[v] != -1) solve(heavy[v], true);
        for (int u : tree[v]) if (parent[u] == v && u != heavy[v]) add_subtree(u, 1);
        distinct += (freq[id[v]]++ == 0);
        answer[v] = distinct;
        if (!keep) add_subtree(v, -1);
    };
    solve(0, true);
    return answer;
}
