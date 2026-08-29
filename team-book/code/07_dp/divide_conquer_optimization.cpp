/*
@title: Divide & Conquer DP
@complexity: O(m n log n)
@tags: DP optimization, monotone opt
@priority: 20
*/

/*
    DP of the form:
        dp[i][j] = min_{0 <= k <= j} dp[i-1][k-1] + C(k,j)
    where opt[i][j] is monotone:
        opt[i][j] <= opt[i][j+1]
    Sufficient condition:
        C(a,c) + C(b,d) <= C(a,d) + C(b,c)
        for a <= b <= c <= d.
    IMPORTANT:
        If exactly i groups are required, the valid range
        of k usually needs an additional lower bound.
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
    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);
    for (int j = 0; j < n; j++)
        dp_before[j] = C(0, j);
    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }
    return dp_before[n - 1];
}