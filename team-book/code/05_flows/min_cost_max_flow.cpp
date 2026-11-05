/*
@title: Min-Cost Max-Flow
@complexity: O(F E log V) with nonnegative reduced costs
@tags: flow, shortest paths, potentials
@priority: 37
*/

#include <bits/stdc++.h>
using namespace std;

struct MinCostMaxFlow {
    struct Edge { int to, rev, cap; long long cost; };
    int n;
    vector<vector<Edge>> graph;
    explicit MinCostMaxFlow(int size) : n(size), graph(size) {}

    void add_edge(int u, int v, int cap, long long cost) {
        int rev_u = (int)graph[v].size();
        int rev_v = (int)graph[u].size();
        if (u == v) ++rev_u;
        Edge a{v, rev_u, cap, cost};
        Edge b{u, rev_v, 0, -cost};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }

    pair<int, long long> run(int source, int sink, int flow_limit = INT_MAX) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> potential(n, 0), dist(n);
        vector<int> parent_v(n), parent_e(n);
        // Initial shortest distances support negative forward costs. The input
        // residual graph must not contain a source-reachable negative cycle.
        vector<char> in_queue(n, false);
        queue<int> initial_queue;
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;
        initial_queue.push(source);
        in_queue[source] = true;
        while (!initial_queue.empty()) {
            int v = initial_queue.front(); initial_queue.pop();
            in_queue[v] = false;
            for (const Edge &e : graph[v]) if (e.cap > 0 && dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                if (!in_queue[e.to]) in_queue[e.to] = true, initial_queue.push(e.to);
            }
        }
        for (int v = 0; v < n; ++v) if (dist[v] < INF) potential[v] = dist[v];
        int flow = 0;
        long long cost = 0;
        while (flow < flow_limit) {
            fill(dist.begin(), dist.end(), INF);
            dist[source] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
            pq.push({0, source});
            while (!pq.empty()) {
                auto [d, v] = pq.top(); pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)graph[v].size(); ++i) {
                    const Edge &e = graph[v][i];
                    if (e.cap == 0) continue;
                    long long nd = d + e.cost + potential[v] - potential[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        parent_v[e.to] = v;
                        parent_e[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[sink] == INF) break;
            for (int v = 0; v < n; ++v) if (dist[v] < INF) potential[v] += dist[v];
            int add = flow_limit - flow;
            for (int v = sink; v != source; v = parent_v[v])
                add = min(add, graph[parent_v[v]][parent_e[v]].cap);
            for (int v = sink; v != source; v = parent_v[v]) {
                Edge &e = graph[parent_v[v]][parent_e[v]];
                cost += (long long)add * e.cost;
                e.cap -= add;
                graph[v][e.rev].cap += add;
            }
            flow += add;
        }
        return {flow, cost};
    }
};
