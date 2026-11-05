/*
@title: Rerooting DP (Sum of Distances)
@complexity: O(n)
@tags: trees, rerooting, DP
@priority: 32
*/

#include <bits/stdc++.h>
using namespace std;

// Computes, for every vertex, the sum of its distances to all vertices.
vector<long long> sum_distances_from_every_vertex(const vector<vector<int>> &tree) {
    int n = (int)tree.size();
    vector<int> parent(n, -1), order;
    vector<long long> subtree_size(n, 1), answer(n);
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
        int v = order[i];
        subtree_size[parent[v]] += subtree_size[v];
        answer[0] += subtree_size[v];
    }
    for (int v : order) {
        for (int u : tree[v]) if (parent[u] == v)
            answer[u] = answer[v] + n - 2 * subtree_size[u];
    }
    return answer;
}
