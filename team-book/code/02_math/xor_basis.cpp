/*
@title: XOR Basis (64-bit)
@complexity: O(64) per insertion, representation, or query
@tags: linear basis, rank, representation, maximum XOR, subset counting
@priority: 30
*/

#include <bits/stdc++.h>
using namespace std;

struct XorBasis {
    using ull = unsigned long long;
    static constexpr int BITS = 64;

    // basis[b] has highest set bit b. coefficient[b] expresses that vector
    // as a subset of the independent vectors in insertion order.
    array<ull, BITS> basis{};
    array<ull, BITS> coefficient{};
    int rank = 0;

    // Returns true exactly when x increases the rank.
    bool insert(ull x) {
        ull used = (rank < BITS ? (1ULL << rank) : 0);
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1ULL) == 0) continue;
            if (basis[bit]) {
                x ^= basis[bit];
                used ^= coefficient[bit];
            } else {
                basis[bit] = x;
                coefficient[bit] = used;
                ++rank;
                return true;
            }
        }
        return false;
    }

    // If x is representable, writes the subset mask in independent-vector
    // insertion order to mask. A 64-bit input has at most 64 such vectors.
    bool representation(ull x, ull &mask) const {
        mask = 0;
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1ULL) == 0) continue;
            if (!basis[bit]) return false;
            x ^= basis[bit];
            mask ^= coefficient[bit];
        }
        return x == 0;
    }

    bool contains(ull x) const {
        ull unused;
        return representation(x, unused);
    }

    // Maximum or minimum value among seed XOR every subset-XOR in the basis.
    ull max_xor(ull seed = 0) const {
        for (int bit = BITS - 1; bit >= 0; --bit)
            seed = max(seed, seed ^ basis[bit]);
        return seed;
    }

    ull min_xor(ull seed = 0) const {
        for (int bit = BITS - 1; bit >= 0; --bit)
            seed = min(seed, seed ^ basis[bit]);
        return seed;
    }

    static ull pow_mod(ull a, ull e, ull mod) {
        assert(mod > 0);
        ull result = 1 % mod;
        while (e) {
            if (e & 1) result = (unsigned __int128)result * a % mod;
            a = (unsigned __int128)a * a % mod;
            e >>= 1;
        }
        return result;
    }

    // Counts subsets of the original n input values whose XOR equals target.
    // Requires mod > 0 and n >= rank.
    ull count_subsets_mod(int n, ull target, ull mod) const {
        assert(mod > 0 && n >= rank);
        if (!contains(target)) return 0;
        return pow_mod(2, n - rank, mod);
    }
};
