/*
@title: KMP Prefix Function and Search
@complexity: O(n + m)
@tags: strings, pattern matching, prefix function
@priority: 20
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(const string &text, const string &pattern) {
    if (pattern.empty()) {
        vector<int> matches(text.size() + 1);
        iota(matches.begin(), matches.end(), 0);
        return matches;
    }
    vector<int> pi = prefix_function(pattern), matches;
    for (int i = 0, j = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == (int)pattern.size()) {
            matches.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return matches;
}
