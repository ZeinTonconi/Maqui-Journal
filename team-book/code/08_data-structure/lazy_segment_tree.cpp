#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct LazySegTree {
    int n;
    vector<ll> st, lazy;

    LazySegTree(const vector<ll>& a) {
        n = (int)a.size();
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }

    void build(int p, int l, int r, const vector<ll>& a) {
        if (l == r) {
            st[p] = a[l];
            return;
        }

        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p) {
        st[p] = st[p * 2] + st[p * 2 + 1];
    }

    void apply(int p, int l, int r, ll x) {
        st[p] += x * (r - l + 1);
        lazy[p] += x;
    }

    void push(int p, int l, int r) {
        if (lazy[p] == 0 || l == r) return;

        int m = (l + r) / 2;

        apply(p * 2, l, m, lazy[p]);
        apply(p * 2 + 1, m + 1, r, lazy[p]);

        lazy[p] = 0;
    }

    void update(int p, int l, int r,
                int ql, int qr, ll x) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, x);
            return;
        }

        push(p, l, r);

        int m = (l + r) / 2;
        update(p * 2, l, m, ql, qr, x);
        update(p * 2 + 1, m + 1, r, ql, qr, x);

        pull(p);
    }

    ll query(int p, int l, int r,
             int ql, int qr) {
        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr)
            return st[p];

        push(p, l, r);

        int m = (l + r) / 2;

        return query(p * 2, l, m, ql, qr)
             + query(p * 2 + 1, m + 1, r, ql, qr);
    }

    void range_add(int l, int r, ll x) {
        if (l > r) return;
        update(1, 0, n - 1, l, r, x);
    }

    ll range_sum(int l, int r) {
        if (l > r) return 0;
        return query(1, 0, n - 1, l, r);
    }
};