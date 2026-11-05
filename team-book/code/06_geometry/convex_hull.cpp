/*
@title: Convex Hull (Monotone Chain)
@complexity: O(n log n)
@tags: geometry, convex hull, integer points
@priority: 44
*/

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point &other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator==(const Point &other) const { return x == other.x && y == other.y; }
};

__int128 cross(const Point &a, const Point &b, const Point &c) {
    return ((__int128)b.x - a.x) * ((__int128)c.y - a.y)
         - ((__int128)b.y - a.y) * ((__int128)c.x - a.x);
}

// Returns the convex hull counterclockwise, excluding collinear points on edges.
vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) return points;
    vector<Point> hull;
    for (const Point &p : points) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    size_t lower_size = hull.size();
    for (int i = (int)points.size() - 2; i >= 0; --i) {
        const Point &p = points[i];
        while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    hull.pop_back();
    return hull;
}
