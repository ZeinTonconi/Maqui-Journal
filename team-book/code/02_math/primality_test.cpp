/*
@title: Miller-Rabin Primality Test
@complexity: O(log^3 n) worst-case, 64-bit
@tags: primality, modular exponentiation
@priority: 30
*/

using ull = unsigned long long;
using u128 = __uint128_t;

ull mod_pow(ull a, ull e, ull mod) {
    ull r = 1;
    while (e) {
        if (e & 1)
            r = (u128)r * a % mod;
        a = (u128)a * a % mod;
        e >>= 1;
    }
    return r;
}

bool isPrime(ull n) {
    if (n < 2)
        return false;
for (ull p : {
        2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL,
        17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL
    }) {
        if (n % p == 0)
            return n == p;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (ull a : {
        2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL,
        17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL
    }) {
        if (a >= n)
            continue;
        ull x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool witness = true;
        for (int r = 1; r < s; ++r) {
            x = (u128)x * x % n;
            if (x == n - 1) {
                witness = false;
                break;
            }
        }
        if (witness)
            return false;
    }
    return true;
}