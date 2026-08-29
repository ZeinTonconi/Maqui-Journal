/*
@title: Chinese Remainder Theorem
@category: Math
@complexity: O(N)
@tags: modular arithmetic, number theory
*/

struct Congruence {
    long long a, m;
};

long long mod_inv(long long a, long long m) {
    long long x, y;
    extgcd(a, m, x, y);
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
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}