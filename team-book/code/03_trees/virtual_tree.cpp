/*
@title: Virtual Tree
@complexity: O(k log k) including sorting
@tags: trees, LCA, tree compression
@priority: 31
*/

#include <bits/stdc++.h>
using namespace std;

// tin must be a DFS entry time, and lca(u, v) must return the tree LCA.
// Returns a tree over original vertex ids; callers can store weights separately.
vector<vector<int>> build_virtual_tree(
    vector<int> nodes,
    const vector<int> &tin,
    const function<int(int, int)> &lca
) {
    if (nodes.empty()) return vector<vector<int>>(tin.size());
    sort(nodes.begin(), nodes.end(), [&](int a, int b) { return tin[a] < tin[b]; });
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    int k = (int)nodes.size();
    for (int i = 1; i < k; ++i) nodes.push_back(lca(nodes[i - 1], nodes[i]));
    sort(nodes.begin(), nodes.end(), [&](int a, int b) { return tin[a] < tin[b]; });
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    vector<vector<int>> tree(tin.size());
    vector<int> st;
    for (int v : nodes) {
        while (!st.empty() && lca(st.back(), v) != st.back()) st.pop_back();
        if (!st.empty()) {
            tree[st.back()].push_back(v);
            tree[v].push_back(st.back());
        }
        st.push_back(v);
    }
    return tree;
}
