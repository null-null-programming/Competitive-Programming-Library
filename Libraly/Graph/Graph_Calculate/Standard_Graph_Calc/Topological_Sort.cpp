class TopoSort {
private:
  int N;
  vector<vector<int>> G;
  vector<int> indeg;
  vector<bool> V;
  list<int> out;

  void add_edge(int from, int to) {
    G[from].push_back(to);
  }

  void bfs(int s) {
    queue<int> q;
    q.push(s);
    V[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      out.push_back(u);
      for (auto v : G[u]) {
        indeg[v]--;
        if (indeg[v] == 0 && V[v] != true) {
          V[v] = true;
          q.push(v);
        }
      }
    }
  }

  list<int> do_topoSort() {
    for (int i = 0; i < N; i++) {
      indeg[i] = 0;
    }
    for (int i = 0; i < N; i++) {
      for (auto v : G[i]) {
        indeg[v]++;
      }
    }
    for (int i = 0; i < N; i++) {
      if (indeg[i] == 0 && V[i] != true) {
        bfs(i);
      }
    }
    return out;
  }

public:
  TopoSort(int N) : N(N), G(N, vector<int>()), indeg(N), V(N, false) {}

  void addEdge(int from, int to) { return add_edge(from, to); }
  list<int> topoSort() { return do_topoSort(); }
};
