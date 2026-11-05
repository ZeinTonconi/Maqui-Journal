/*
@title: Miller-Rabin and Pollard Rho Factorization
@complexity: Expected sublinear per factor for 64-bit integers
@tags: number theory, primality, factorization
@priority: 41
*/

#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;

u64 mod_mul(u64 a, u64 b, u64 mod) { return (u128)a * b % mod; }

u64 mod_pow(u64 a, u64 e, u64 mod) {
    u64 result = 1;
    while (e) {
        if (e & 1) result = mod_mul(result, a, mod);
        a = mod_mul(a, a, mod);
        e >>= 1;
    }
    return result;
}

bool is_prime_u64(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, ++s;
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = mod_pow(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (u64 r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        u64 c = rng() % (n - 1) + 1;
        u64 x = rng() % (n - 2) + 2, y = x, divisor = 1;
        auto f = [&](u64 v) { return (u64)(((u128)mod_mul(v, v, n) + c) % n); };
        for (int iter = 0; divisor == 1 && iter < 200000; ++iter) {
            x = f(x); y = f(f(y));
            u64 diff = x > y ? x - y : y - x;
            divisor = gcd(diff, n);
        }
        if (divisor > 1 && divisor < n) return divisor;
    }
}

void factorize_u64(u64 n, map<u64, int> &factors) {
    if (n == 1) return;
    if (is_prime_u64(n)) { ++factors[n]; return; }
    u64 d = pollard_rho(n);
    factorize_u64(d, factors);
    factorize_u64(n / d, factors);
}
