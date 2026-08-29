/*
@title: 2-SAT
@complexity: O(n + m)
@tags: SCC, implication graph, satisfiability
@priority: 20
*/

struct TwoSat {
    int n;

    vector<vector<int>> g, rg;
    vector<int> comp, order;
    vector<char> used;
    vector<bool> assignment;

    TwoSat(int n)
        : n(n),
          g(2 * n),
          rg(2 * n),
          comp(2 * n, -1),
          order(),
          used(2 * n, false),
          assignment(n, false) {}

    int node(int x, bool neg) {
        return 2 * x + neg;
    }

    void add_clause(
        int a, bool na,
        int b, bool nb
    ) {
        int A = node(a, na);
        int B = node(b, nb);
        g[A ^ 1].push_back(B);
        g[B ^ 1].push_back(A);
        rg[B].push_back(A ^ 1);
        rg[A].push_back(B ^ 1);
    }

    void dfs1(int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : rg[v]) {
            if (comp[u] == -1)
                dfs2(u, c);
        }
    }

    bool solve() {
        fill(used.begin(), used.end(), false);
        order.clear();
        for (int v = 0; v < 2 * n; v++) {
            if (!used[v])
                dfs1(v);
        }
        fill(comp.begin(), comp.end(), -1);
        int components = 0;
        for (int i = 2 * n - 1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1)
                dfs2(v, components++);
        }
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1])
                return false;
            assignment[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};