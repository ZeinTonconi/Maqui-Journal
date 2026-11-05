/*
@title: Hopcroft-Karp Bipartite Matching
@complexity: O(E sqrt(V))
@tags: bipartite matching, maximum matching
@priority: 36
*/

#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int left_size, right_size;
    vector<vector<int>> adj;
    vector<int> match_left, match_right, dist;

    int shortest_distance = INT_MAX;

    HopcroftKarp(int left_count, int right_count)
        : left_size(left_count), right_size(right_count), adj(left_count),
          match_left(left_count, -1), match_right(right_count, -1), dist(left_count) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < left_size; ++u) {
            if (match_left[u] == -1) dist[u] = 0, q.push(u);
            else dist[u] = -1;
        }
        int shortest = INT_MAX;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] + 1 > shortest) continue;
            for (int v : adj[u]) {
                int next = match_right[v];
                if (next == -1) shortest = dist[u] + 1;
                else if (dist[next] == -1) dist[next] = dist[u] + 1, q.push(next);
            }
        }
        shortest_distance = shortest;
        return shortest != INT_MAX;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int next = match_right[v];
            if ((next == -1 && dist[u] + 1 == shortest_distance) ||
                (next != -1 && dist[next] == dist[u] + 1 && dfs(next))) {
                match_left[u] = v;
                match_right[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maximum_matching() {
        int result = count_if(match_left.begin(), match_left.end(), [](int v) { return v != -1; });
        while (bfs()) {
            for (int u = 0; u < left_size; ++u)
                if (match_left[u] == -1 && dfs(u)) ++result;
        }
        return result;
    }
};
