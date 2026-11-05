/*
@title: Li Chao Tree (Maximum, Discrete Coordinates)
@complexity: O(log X) per insertion or query
@tags: data structures, lines, DP optimization
@priority: 34
*/

#include <bits/stdc++.h>
using namespace std;

struct LiChaoTree {
    struct Line {
        long long m = 0, b = 0;
        long long eval(long long x) const { return m * x + b; }
    };
    vector<long long> xs;
    vector<Line> tree;
    vector<char> has;

    explicit LiChaoTree(vector<long long> coordinates) : xs(move(coordinates)) {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        tree.resize(max(1, 4 * (int)xs.size()));
        has.assign(tree.size(), false);
    }

    void add_line(Line line) { if (!xs.empty()) add_line(1, 0, (int)xs.size() - 1, line); }

    void add_line(int p, int l, int r, Line line) {
        if (!has[p]) { tree[p] = line; has[p] = true; return; }
        int mid = (l + r) / 2;
        bool left = line.eval(xs[l]) > tree[p].eval(xs[l]);
        bool middle = line.eval(xs[mid]) > tree[p].eval(xs[mid]);
        if (middle) swap(line, tree[p]);
        if (l == r) return;
        if (left != middle) add_line(p * 2, l, mid, line);
        else add_line(p * 2 + 1, mid + 1, r, line);
    }

    long long query(long long x) const {
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        assert(i < (int)xs.size() && xs[i] == x);
        return query(1, 0, (int)xs.size() - 1, i);
    }

    long long query(int p, int l, int r, int i) const {
        long long result = has[p] ? tree[p].eval(xs[i]) : LLONG_MIN;
        if (l == r) return result;
        int mid = (l + r) / 2;
        long long child = i <= mid ? query(p * 2, l, mid, i)
                                   : query(p * 2 + 1, mid + 1, r, i);
        return max(result, child);
    }
};
