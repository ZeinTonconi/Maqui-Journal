/*
@title: Chinese Remainder Theorem
@category: Math
@complexity: O(N)
@tags: modular arithmetic, number theory, pairwise coprime moduli
*/

struct Congruence {
    long long a, m;
};

// This version assumes positive, pairwise-coprime moduli and that their
// product fits in signed 64-bit arithmetic.
long long crt_extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = crt_extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long mod_inv(long long a, long long m) {
    long long x, y;
    crt_extgcd(a, m, x, y);
    return ((x % m) + m) % m;
}

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        a_i = (a_i % congruence.m + congruence.m) % congruence.m;
        solution = (solution + (__int128)a_i * M_i % M * N_i) % M;
    }
    return solution;
}
