//O(V log E)

class Dijkstra {
private:
  struct edge {
    int to, cost;
  };

  const int INF = 1e18;

  int V;
  vector<vector<edge>> G;
  vector<int> d;

  void add_edge(int from, int to, int cost) {
    G[from].push_back({to, cost});
    G[to].push_back({from, cost});
  }

  void do_dijkstra(int s) {
    using P = pair<int, int>;
    priority_queue<P, vector<P>, greater<P>> que;
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
      P p = que.top();
      que.pop();
      int v = p.second;
      if (d[v] < p.first)
        continue;
      for (int i = 0; i < G[v].size(); i++) {
        edge e = G[v][i];
        if (d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          que.push(P(d[e.to], e.to));
        }
      }
    }
  }

public:
  Dijkstra(int V) : V(V), G(V, vector<edge>()), d(V) {}

  void addEdge(int from, int to, int cost) { return add_edge(from, to, cost); }
  void dijkstra(int s) { return do_dijkstra(s); }
  int get(int v) { return d[v]; }
};
