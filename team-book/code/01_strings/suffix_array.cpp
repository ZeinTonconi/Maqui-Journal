/*
@title: Suffix Array
@category: Strings
@complexity: O(N log N)
@tags: suffix array, string matching
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(string s) {
	s += char(0);
	const int n = s.size();
	vector<int> a(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j) {
		return s[i] < s[j];	
	});
	vector<int> mapping(n);
	mapping[a[0]] = 0;
	for(int i = 1; i < n; i++) mapping[a[i]] = mapping[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	int len = 1;
	vector<int> sbs(n);
	vector<int> head(n);
	vector<int> new_mapping(n);
	while(len < n) {
		for(int i = 0; i < n; i++) sbs[i] = (a[i] + n - len) % n;
		for(int i = n - 1; i >= 0; i--) head[mapping[a[i]]] = i;
		for(int i = 0; i < n; i++) {
			int x = sbs[i];
			a[head[mapping[x]]++] = x;
		}
		new_mapping[a[0]] = 0;
		for(int i = 1; i < n; i++) {
			if(mapping[a[i - 1]] != mapping[a[i]]) {
				new_mapping[a[i]] = new_mapping[a[i - 1]] + 1;
			}
			else {
				int pre = mapping[(a[i - 1] + len) % n];
				int cur = mapping[(a[i] + len) % n];
				new_mapping[a[i]] = new_mapping[a[i - 1]] + (pre != cur);
			}
		}
		len <<= 1;
		swap(mapping, new_mapping);
	}
	return vector<int>(a.begin() + 1, a.end()); // Ignores a[0] since it's sentinel character.
}

vector<int> lcp_array(vector<int> &a, string s) {
	const int n = s.size();
	vector<int> rank(n);
	for(int i = 0; i < n; i++) rank[a[i]] = i;
	int k = 0;
	vector<int> lcp(n);
	for(int i = 0; i < n; i++) {
		if(rank[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
		lcp[rank[i]] = k;
		if(k) k--;
	}
	lcp.pop_back();
	return lcp;
}

int main() {
	cin.tie(0) -> sync_with_stdio(false);
	vector<int> a = suffix_array("abcbcba");
	vector<int> lcp = lcp_array(a, "abcbcba");
	for(auto x : a) cout << x << " \n"[x == a.back()];
	for(auto x : lcp) cout << x << " \n"[x == lcp.back()];
	return 0;
}