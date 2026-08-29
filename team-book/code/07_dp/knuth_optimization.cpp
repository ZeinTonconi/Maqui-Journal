/*
@title: Knuth Optimization
@complexity: O(n^2)
@tags: interval DP, DP optimization
@priority: 30
*/

/*
    dp[l][r] = minimum cost for interval [l,r).
    Transition:
        dp[l][r] = min(dp[l][k] + dp[k][r] + C(l,r))   for l < k < r
    Knuth condition:
        opt[l][r-1] <= opt[l][r] <= opt[l+1][r]
    Base:
        dp[i][i] = 0, dp[i][i+1] = 0 (single element, no split needed)
    Requires C to satisfy the quadrangle inequality + monotonicity
    (true e.g. for C(l,r) = prefix[r]-prefix[l] with non-negative weights).
*/

using ll = long long;
vector<vector<ll>> knuth(int n, const vector<ll>& prefix) {
    const ll INF = (1LL << 62);
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    vector<vector<int>> opt(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= n; i++)
        opt[i][i] = i;
    for (int i = 0; i < n; i++)
        opt[i][i + 1] = i;   // seed the length-1 boundary (was left at 0 before!)

    auto C = [&](int l, int r) -> ll {
        return prefix[r] - prefix[l];
    };

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            dp[l][r] = INF;
            int L = max(opt[l][r - 1], l + 1);
            int R = min(opt[l + 1][r], r - 1);
            for (int k = L; k <= R; k++) {
                ll val = dp[l][k] + dp[k][r] + C(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp;
}