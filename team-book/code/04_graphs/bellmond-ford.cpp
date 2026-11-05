/*
@title: Bellman-Ford Algorithm
@category: Graphs
@complexity: O(VE)
@tags: shortest path, negative weights
*/

struct Edge {
    int a, b;
    long long cost;
};

int n;
vector<Edge> edges;
void solve() {
    vector<__int128> d(n, 0);
    vector<int> p(n, -1);
    int x = -1;

    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges) {
            __int128 candidate = d[e.a] + e.cost;
            if (candidate < d[e.b]) {
                d[e.b] = candidate;
                p[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if (x == -1) {
        cout << "No negative cycle found.";
    } else {
        for (int i = 0; i < n; ++i)
            x = p[x];

        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        cout << "Negative cycle: ";
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
    }
}
