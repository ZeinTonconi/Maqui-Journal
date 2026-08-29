/*
@title: Eulerian Path
@category: Graphs
@complexity: O(V^2 + E)
@tags: graph traversal, Hierholzer's algorithm
@input: n, then n x n adjacency matrix (undirected multigraph, NO self-loops)
@output: sequence of vertices of an Eulerian path/circuit, or -1 if none exists
*/

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> g[i][j];

    // Self-loops never change whether an Eulerian path/circuit exists (they
    // are entered and exited at the same vertex), but this matrix-based
    // traversal cannot consume them correctly (it decrements the same cell
    // twice per step and hangs forever). Strip them before running.
    // If your problem needs self-loops printed, remember how many each
    // vertex had and splice them into the output wherever that vertex
    // appears in the final trail.
    for (int i = 0; i < n; ++i)
        g[i][i] = 0;

    vector<int> deg(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j];

    int first = 0;
    while (first < n && !deg[first])
        ++first;
    if (first == n) {
        cout << -1 << "\n"; // no edges at all
        return 0;
    }

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else bad = true;
        }
    }

    if (v1 != -1)
        ++g[v1][v2], ++g[v2][v1];

    stack<int> st;
    st.push(first);
    vector<int> res;
    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i]) break;
        if (i == n) {
            res.push_back(v);
            st.pop();
        } else {
            --g[v][i];
            --g[i][v];
            st.push(i);
        }
    }

    if (v1 != -1) {
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (g[i][j]) bad = true; // leftover edges => graph was disconnected

    if (bad) {
        cout << -1 << "\n";
    } else {
        for (int x : res) cout << x << " ";
        cout << "\n";
    }
}