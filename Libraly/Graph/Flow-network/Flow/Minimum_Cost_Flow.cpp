//O(F*V^2)

class MinimumCostFlow {
private:
  struct edge {
    int to, cap, cost, rev;
  };

  const int INF = 1e18;

  int V;
  vector<vector<edge>> G;
  vector<int> h, dist;
  vector<int> prevv, preve;

  void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back({to, cap, cost, (int)G[to].size()});
    G[to].push_back({from, 0LL, -cost, (int)G[from].size() - 1LL});
  }

  int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill(h.begin(), h.end(), 0LL);

    while (f > 0) {
      using P = pair<int, int>;
      priority_queue<P, vector<P>, greater<P>> que;
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      que.push(P(0, s));

      while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); i++) {
          edge &e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            que.push(P{dist[e.to], e.to});
          }
        }
      }

      if (dist[t] == INF) {
        return -1;
      }

      for (int v = 0; v < V; v++) {
        h[v] += dist[v];
      }

      int d = f;
      for (int v = t; v != s; v = prevv[v]) {
        d = min(d, G[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }

public:
  MinimumCostFlow(int N) : V(N), G(N, vector<edge>()), h(N), dist(N), prevv(N), preve(N) {}

  void addEdge(int from, int to, int cap, int cost) {
    return add_edge(from, to, cap, cost);
  }
  int minCostFlow(int s, int t, int f) {
    return min_cost_flow(s, t, f);
  }
};
