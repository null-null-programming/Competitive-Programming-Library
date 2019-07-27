//O(E*V^2)

class Dinic {
private:
  struct edge {
    int to, cap, rev;
  };

  const int INF = 1e18;

  vector<vector<edge>> G;
  vector<int> level, iter;

  void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, (int)G[to].size()});
    G[to].push_back((edge){from, 0LL, (int)G[from].size() - 1LL});
  }

  void bfs(int s) {
    fill(level.begin(), level.end(), -1);
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
      }
    }
  }

  int dfs(int v, int t, int f) {
    if (v == t)
      return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
      edge &e = G[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  int getMaxFlow(int s, int t) {
    int flow = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0)
        return flow;
      fill(iter.begin(), iter.end(), 0);
      int f;
      while ((f = dfs(s, t, INF)) > 0) {
        flow += f;
      }
    }
  }

public:
  Dinic(int N) : G(N, vector<edge>()) {
    level.resize(N);
    iter.resize(N);
  }

  void addEdge(int from, int to, int cap) { add_edge(from, to, cap); }
  int maxFlow(int s, int t) { return getMaxFlow(s, t); }
};
