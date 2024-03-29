//O(VE)
class BellmanFord {
private:
  struct edge {
    int from, to, cost;
  };

  const int INF = 1e18;
  int V, E;
  vector<edge> es;
  vector<int> d;

  void add_edge(int from, int to, int cost) {
    es.push_back({from, to, cost});
  }
  bool shortest_path(int s) {
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    for (int i = 0; i < V; i++) {
      bool update = false;
      for (auto e : es) {
        if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
          d[e.to] = d[e.from] + e.cost;
          update = true;
          if (i == V - 1) return false;
        }
      }
      if (!update) break;
    }
    return true;
  }
  int get_shortest_dist(int v) {
    return d[v];
  }

public:
  BellmanFord(int V, int E) : V(V), E(E), es(E), d(V) {}

  void addEdge(int from, int to, int cost) { return add_edge(from, to, cost); }
  bool init(int s) { return shortest_path(s); }
  int dist(int v) { return get_shortest_dist(v); }
};
