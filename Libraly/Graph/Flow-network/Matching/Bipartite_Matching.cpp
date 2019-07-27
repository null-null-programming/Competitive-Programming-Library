//O(VE)

class BipartiteMatching {
private:
  int V;
  vector<int> match;
  vector<vector<int>> G;
  vector<bool> used;

  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
      int u = G[v][i], w = match[u];
      if (w < 0 || ((!used[w]) && dfs(w))) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }

  int bipartite_matching() {
    int res = 0;
    fill(match.begin(), match.end(), -1);
    for (int v = 0; v < V; v++) {
      if (match[v] < 0) {
        fill(used.begin(), used.end(), 0);
        if (dfs(v)) res++;
      }
    }
    return res;
  }

public:
  BipartiteMatching(int N) : V(N), G(N, vector<int>()) {
    match.resize(V);
    used.resize(V);
  }

  void addEdge(int u, int v) { return add_edge(u, v); }
  int getNum() { return bipartite_matching(); }
};
