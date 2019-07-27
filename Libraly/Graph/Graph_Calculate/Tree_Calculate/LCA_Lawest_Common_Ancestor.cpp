//pre:O(nlog n)
//query:O(log n)

class LCA {
private:
  int V, LV;
  int root;
  vector<vector<int>> G, parent;
  vector<int> depth;

  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (int i = 0; i < G[v].size(); i++) {
      if (G[v][i] != p)
        dfs(G[v][i], v, d + 1);
    }
  }
  void get_init() {
    dfs(root, -1, 0);
    for (int k = 0; k + 1 < LV; k++) {
      for (int v = 0; v < V; v++) {
        if (parent[k][v] < 0)
          parent[k + 1][v] = -1;
        else
          parent[k + 1][v] = parent[k][parent[k][v]];
      }
    }
  }
  int get_lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < LV; k++) {
      if ((depth[v] - depth[u]) >> k & 1) {
        v = parent[k][v];
      }
    }
    if (u == v) return u;
    for (int k = LV - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }

public:
  LCA(int V, int root) : V(V), root(root), G(V, vector<int>()), depth(V) {
    int v_ = 1, cnt = 0;
    while (v_ < V) v_ *= 2, cnt++;
    LV = cnt;
    parent.resize(LV, vector<int>(V));
  }

  void init() { return get_init(); }
  void addEdge(int u, int v) { return add_edge(u, v); }
  int get(int u, int v) { return get_lca(u, v); }
};
