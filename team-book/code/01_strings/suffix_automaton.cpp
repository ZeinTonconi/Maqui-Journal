/*
@title: Suffix Automaton
@complexity: O(n) states and transitions (fixed alphabet)
@tags: strings, substrings, occurrence counts
@priority: 38
*/

#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int link = -1, len = 0;
        long long occurrences = 0;
        array<int, 26> next;
        State() { next.fill(-1); }
    };
    vector<State> st;
    int last = 0;

    explicit SuffixAutomaton(int max_length = 0) {
        st.reserve(2 * max_length + 1);
        st.emplace_back();
    }

    void extend(char ch) {
        int c = ch - 'a';
        assert(0 <= c && c < 26); // This template uses the lowercase English alphabet.
        int cur = (int)st.size(); st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].occurrences = 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) st[p].next[c] = cur, p = st[p].link;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = (int)st.size(); st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].occurrences = 0;
                while (p != -1 && st[p].next[c] == q) st[p].next[c] = clone, p = st[p].link;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void build(const string &s) { for (char c : s) extend(c); }

    void propagate_occurrences() {
        vector<int> order(st.size()); iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return st[a].len > st[b].len; });
        for (int v : order) if (st[v].link != -1)
            st[st[v].link].occurrences += st[v].occurrences;
    }

    bool contains(const string &pattern) const {
        int v = 0;
        for (char ch : pattern) {
            int c = ch - 'a';
            if (c < 0 || c >= 26 || st[v].next[c] == -1) return false;
            v = st[v].next[c];
        }
        return true;
    }
};
