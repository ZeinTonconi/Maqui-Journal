/*
@title: Hungarian Algorithm
@complexity: O(n^2 m), O(n^3) if n = m
@tags: assignment problem, minimum-cost matching
@priority: 40
*/

/*
    Minimum-cost assignment.
    A[i][j] = cost of assigning row i to column j.
    n <= m
    Returns:
        ans[i] = column assigned to row i
    Also returns the minimum total cost.
    1-indexed matrix A[1..n][1..m].
    For maximum cost:
        negate all A[i][j].
*/

pair<long long, vector<int>> hungarian(
    const vector<vector<long long>>& A
) {
    int n = (int)A.size() - 1;
    int m = (int)A[0].size() - 1;

    const long long INF = (1LL << 60);

    vector<long long> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<long long> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0];
            long long delta = INF;
            int j1 = 0;
            for (int j = 1; j <= m; j++) {
                if (used[j]) continue;

                long long cur = A[i0][j] - u[i0] - v[j];

                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }

                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (int j = 0; j <= m; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        // Restore the augmenting path.
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;

        } while (j0);
    }

    // p[j] = row assigned to column j.
    // Convert to ans[i] = column assigned to row i.
    vector<int> ans(n + 1);

    for (int j = 1; j <= m; j++)
        ans[p[j]] = j;

    return {-v[0], ans};
}