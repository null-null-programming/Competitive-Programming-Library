//O(V+E)
class SCC {
private:
  int V;
  vector<vector<int>> G;
  vector<vector<int>> rG;
  vector<int> vs, cmp;
  vector<bool> used;

  void add_edge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
  }
  void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
      if (!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
  }
  void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rG[v].size(); i++) {
      if (!used[rG[v][i]]) rdfs(rG[v][i], k);
    }
  }
  vector<int> do_scc() {
    fill(used.begin(), used.end(), 0);
    vs.clear();
    for (int v = 0; v < V; v++) {
      if (!used[v]) dfs(v);
    }
    fill(used.begin(), used.end(), 0);
    int k = 0;
    for (int i = vs.size() - 1; i >= 0; i--) {
      if (!used[vs[i]]) rdfs(vs[i], k++);
    }
    return cmp;
  }

public:
  SCC(int V) : V(V), G(V, vector<int>()), rG(V, vector<int>()), vs(V), cmp(V), used(V) {}

  void addEdge(int from, int to) { return add_edge(from, to); }
  vector<int> scc() { return do_scc(); }
};
