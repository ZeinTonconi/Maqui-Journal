/*
@title: Convex Hull Trick (Monotone Maximum)
@complexity: Amortized O(1) per insertion and query
@tags: DP optimization, lines, convex hull trick
@priority: 43
*/

#include <bits/stdc++.h>
using namespace std;

struct MonotoneMaxCHT {
    struct Line {
        long long m, b;
        long long eval(long long x) const { return m * x + b; }
    };
    deque<Line> hull;

    // Add slopes in strictly increasing order (equal slopes keep the larger intercept).
    void add_line(long long m, long long b) {
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b >= b) return;
            hull.pop_back();
        }
        while (hull.size() >= 2) {
            Line a = hull[hull.size() - 2], c = hull.back();
            if (((__int128)a.b - c.b) * ((__int128)m - c.m) <
                ((__int128)c.b - b) * ((__int128)c.m - a.m)) break;
            hull.pop_back();
        }
        hull.push_back({m, b});
    }

    // Query x values in nondecreasing order.
    long long query(long long x) {
        assert(!hull.empty());
        while (hull.size() >= 2 && hull[0].eval(x) <= hull[1].eval(x)) hull.pop_front();
        return hull.front().eval(x);
    }
};
