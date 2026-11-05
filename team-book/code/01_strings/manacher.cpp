/*
@title: Manacher's Algorithm
@category: Strings
@complexity: O(N)
@tags: palindrome, string manipulation
*/

vector<int> manacher_odd(string s) {
    int n = s.size();
    vector<int> radius(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r ? 1 : min(radius[l + r - i], r - i + 1));
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
        radius[i] = k;
        if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
    }
    return radius;
}

vector<int> manacher(string s) {
    if (s.empty()) return {};
    // Integer separators cannot collide with any byte in the input string.
    vector<int> t(2 * s.size() + 1, 0);
    for (int i = 0; i < (int)s.size(); ++i)
        t[2 * i + 1] = (unsigned char)s[i] + 1;
    int n = (int)t.size();
    vector<int> radius(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r ? 1 : min(radius[l + r - i], r - i + 1));
        while (i - k >= 0 && i + k < n && t[i - k] == t[i + k]) ++k;
        radius[i] = k;
        if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
    }
    return vector<int>(radius.begin() + 1, radius.end() - 1);
}
