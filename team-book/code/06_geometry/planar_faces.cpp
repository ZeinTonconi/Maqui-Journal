/*
@title: Faces of a Planar Graph
@complexity: O(m log m)
@tags: planar graph, faces, embedding
@priority: 40
*/

/*
    Input:
        - Connected planar graph
        - Straight-line embedding
        - vertices[i] = coordinates of vertex i
        - adj[i] = neighbors of vertex i

    Output:
        faces[0] = outer face
        faces[i] = inner faces

    Inner faces are CCW.
    Outer face is CW.

    Vertices are 0-indexed.

    For a planar graph:
        m = O(n)
    so complexity is also O(n log n).

    If adjacency lists are already sorted by angle,
    the traversal itself can be made O(n).
*/

struct Point {
    long long x, y;

    Point(long long x = 0, long long y = 0)
        : x(x), y(y) {}

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    long long cross(const Point& p) const {
        return x * p.y - y * p.x;
    }

    int half() const {
        return y < 0 || (y == 0 && x < 0);
    }
};

vector<vector<int>> planar_faces(
    vector<Point> p,
    vector<vector<int>> adj
) {
    int n = p.size();

    // Sort neighbors counter-clockwise by polar angle.
    vector<vector<char>> used(n);

    for (int i = 0; i < n; i++) {
        used[i].assign(adj[i].size(), false);

        auto cmp = [&](int l, int r) {
            Point a = p[l] - p[i];
            Point b = p[r] - p[i];

            if (a.half() != b.half())
                return a.half() < b.half();

            return a.cross(b) > 0;
        };

        sort(adj[i].begin(), adj[i].end(), cmp);
    }

    vector<vector<int>> faces;

    // Every directed edge belongs to exactly one face.
    for (int s = 0; s < n; s++) {
        for (int e0 = 0; e0 < (int)adj[s].size(); e0++) {
            if (used[s][e0])
                continue;

            vector<int> face;

            int v = s;
            int e = e0;

            while (!used[v][e]) {
                used[v][e] = true;
                face.push_back(v);

                int u = adj[v][e];

                // Find v in adj[u].
                auto cmp = [&](int l, int r) {
                    Point a = p[l] - p[u];
                    Point b = p[r] - p[u];

                    if (a.half() != b.half())
                        return a.half() < b.half();

                    return a.cross(b) > 0;
                };

                int pos = lower_bound(
                    adj[u].begin(),
                    adj[u].end(),
                    v,
                    cmp
                ) - adj[u].begin();

                // Take the next edge clockwise.
                e = (pos + 1) % adj[u].size();
                v = u;
            }

            reverse(face.begin(), face.end());

            // Positive signed area -> inner face.
            // Non-positive -> outer face.
            Point p0 = p[face[0]];
            __int128 area = 0;

            for (int i = 0; i < (int)face.size(); i++) {
                Point a = p[face[i]];
                Point b = p[face[(i + 1) % face.size()]];

                area += (a - p0).cross(b - a);
            }

            if (area <= 0)
                faces.insert(faces.begin(), face);
            else
                faces.push_back(face);
        }
    }

    return faces;
}