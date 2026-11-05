/*
@title: Persistent Segment Tree (K-th Smallest)
@complexity: O(log n) per version update or range query
@tags: persistent segment tree, order statistics
@priority: 35
*/

#include <bits/stdc++.h>
using namespace std;

struct PersistentKth {
    struct Node { int left = 0, right = 0, sum = 0; };
    vector<Node> nodes = {Node()};
    vector<int> values, roots;

    explicit PersistentKth(vector<int> a) : values(move(a)) {
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        roots.push_back(0);
    }

    int insert(int old, int l, int r, int pos) {
        int cur = (int)nodes.size();
        nodes.push_back(nodes[old]);
        ++nodes[cur].sum;
        if (l != r) {
            int mid = (l + r) / 2;
            if (pos <= mid) nodes[cur].left = insert(nodes[old].left, l, mid, pos);
            else nodes[cur].right = insert(nodes[old].right, mid + 1, r, pos);
        }
        return cur;
    }

    void build(const vector<int> &a) {
        roots.assign(1, 0);
        for (int x : a) {
            int pos = lower_bound(values.begin(), values.end(), x) - values.begin();
            roots.push_back(values.empty() ? 0 : insert(roots.back(), 0, (int)values.size() - 1, pos));
        }
    }

    // k is 1-indexed; [l, r] is a 0-indexed inclusive range of the original array.
    int kth(int l, int r, int k) const {
        assert(0 <= l && l <= r && r + 1 < (int)roots.size());
        assert(1 <= k && k <= nodes[roots[r + 1]].sum - nodes[roots[l]].sum);
        int a = roots[l], b = roots[r + 1], lo = 0, hi = (int)values.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            int count_left = nodes[nodes[b].left].sum - nodes[nodes[a].left].sum;
            if (k <= count_left) { a = nodes[a].left; b = nodes[b].left; hi = mid; }
            else { k -= count_left; a = nodes[a].right; b = nodes[b].right; lo = mid + 1; }
        }
        return values[lo];
    }
};
