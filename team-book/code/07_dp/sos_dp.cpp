/*
@title: SOS DP (Subset Sums)
@complexity: O(n 2^n)
@tags: bitmask DP, subset aggregation
@priority: 42
*/

#include <bits/stdc++.h>
using namespace std;

// Afterward, subset_sum[mask] is the sum of freq[sub] over all submasks sub of mask.
vector<long long> sos_subset_sums(vector<long long> freq, int bits) {
    assert(bits >= 0 && bits < 31);
    assert((int)freq.size() == (1 << bits));
    for (int bit = 0; bit < bits; ++bit)
        for (int mask = 0; mask < (1 << bits); ++mask)
            if (mask & (1 << bit)) freq[mask] += freq[mask ^ (1 << bit)];
    return freq;
}
