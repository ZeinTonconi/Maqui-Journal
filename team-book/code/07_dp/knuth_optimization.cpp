/*
@title: Knuth Optimization
@complexity: O(n^2)
@tags: interval DP, DP optimization
@priority: 30
*/

/*
    dp[l][r] = minimum cost for interval [l,r).

    Transition:
        dp[l][r] = min(dp[l][k] + dp[k][r] + C(l,r))
            l < k < r
    Knuth condition:
        opt[l][r-1] <= opt[l][r] <= opt[l+1][r]
    Base:
        dp[i][i] = 0
*/

using ll = long long;
vector<vector<ll>> knuth(int n, const vector<ll>& prefix) {
    const ll INF = (1LL << 62);
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));

    vector<vector<int>> opt(n + 1, vector<int>(n + 1));

    for (int i = 0; i <= n; i++)
        opt[i][i] = i;

    auto C = [&](int l, int r) -> ll {
        return prefix[r] - prefix[l];
    };

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            dp[l][r] = INF;
            int L = opt[l][r - 1];
            int R = opt[l + 1][r];
            for (int k = L; k <= R; k++) {
                ll val =dp[l][k] + dp[k][r] + C(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp;
}