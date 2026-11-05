/*
@title: Divide & Conquer DP
@complexity: O(m n log n)
@tags: DP optimization, monotone opt
@priority: 20
*/

/*
    DP of the form:
        dp[g][j] = min_{g-1 <= k <= j} dp[g-1][k-1] + C(k,j)
    where opt[i][j] is monotone:
        opt[i][j] <= opt[i][j+1]
    Sufficient condition:
        C(a,c) + C(b,d) <= C(a,d) + C(b,c)
        for a <= b <= c <= d.
    IMPORTANT:
        solve() computes exactly m nonempty groups. On layer i, k >= i
        guarantees each group contains at least one element.
*/

using ll = long long;

int n, m;
vector<ll> dp_before, dp_cur;

ll C(int k, int j);

void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX,-1};
    for (int k = optl;k <= min(mid, optr);k++) {
        ll val =
            (k ? dp_before[k - 1] : 0)
            + C(k, mid);
        if (val < best.first)
            best = {val, k};
    }
    dp_cur[mid] = best.first;
    int opt = best.second;
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

ll solve() {
    if (n <= 0 || m < 1 || m > n)
        return LLONG_MAX;
    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);
    for (int j = 0; j < n; j++)
        dp_before[j] = C(0, j);
    const ll INF = LLONG_MAX;
    for (int i = 1; i < m; i++) {
        fill(dp_cur.begin(), dp_cur.end(), INF);
        compute(i, n - 1, i, n - 1);
        dp_before = dp_cur;
    }
    return dp_before[n - 1];
}
