/*
@title: Linear Sieve with Möbius Function
@complexity: O(n)
@tags: number theory, sieve, Möbius
@priority: 40
*/

#include <bits/stdc++.h>
using namespace std;

struct MobiusSieve {
    vector<int> mu, primes;
    vector<char> composite;

    explicit MobiusSieve(int n) : mu(n + 1), composite(n + 1, false) {
        if (n >= 1) mu[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!composite[i]) primes.push_back(i), mu[i] = -1;
            for (int p : primes) {
                if (1LL * i * p > n) break;
                composite[i * p] = true;
                if (i % p == 0) { mu[i * p] = 0; break; }
                mu[i * p] = -mu[i];
            }
        }
    }
};
