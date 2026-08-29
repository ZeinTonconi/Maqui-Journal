/*
@title: FFT / NTT Polynomial Multiplication
@complexity: O(n log n)
@tags: convolution, polynomial multiplication, FFT, NTT
@priority: 40
*/

using ll = long long;

using cd = complex<double>;
const double PI = acos(-1.0);

/* ======================== FFT ======================== */

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang =
            2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

vector<ll> multiply_fft(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty())
        return {};
    int need = a.size() + b.size() - 1;
    int n = 1;
    while (n < need)
        n <<= 1;
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<ll> res(need);
    for (int i = 0; i < need; i++)
        res[i] = llround(fa[i].real());

    return res;
}

/* ======================== NTT ======================== */

const ll MOD = 998244353;
const ll ROOT = 3;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<ll>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = mod_pow(
            ROOT,
            (MOD - 1) / len
        );
        if (invert)
            wlen = mod_pow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = u + v < MOD
                    ? u + v
                    : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0
                    ? u - v
                    : u - v + MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = mod_pow(n, MOD - 2);
        for (ll& x : a)
            x = x * inv_n % MOD;
    }
}

vector<ll> multiply_ntt(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty())
        return {};
    int need = a.size() + b.size() - 1;
    int n = 1;
    while (n < need)
        n <<= 1;
    vector<ll> fa(a.begin(), a.end());
    vector<ll> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, true);
    fa.resize(need);
    return fa;
}