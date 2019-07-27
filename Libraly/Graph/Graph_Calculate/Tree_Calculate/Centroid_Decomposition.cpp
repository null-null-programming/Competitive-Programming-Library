//O(V+E)
//木の重心を探す。

struct Centroid {
  //木の重心を一つだけ探す。
  int OneCentroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
    static vector<int> sz((int)g.size());

    function<void(int, int)> get_sz = [&](int u, int prev) {
      sz[u] = 1;
      for (auto v : g[u]) {
        if (v != prev && !dead[v]) {
          get_sz(v, u);
          sz[u] += sz[v];
        }
      }
    };

    get_sz(root, -1);
    int n = sz[root];

    function<int(int, int)> dfs = [&](int u, int prev) {
      for (auto v : g[u]) {
        if (v != prev && !dead[v]) {
          if (sz[v] > n / 2) return dfs(v, u);
        }
      }
      return u;
    };

    return dfs(root, -1);
  }

  //重心分解による分割統治法テンプレート
  void CentroidDecomposition(const vector<vector<int>> &g) {
    int n = (int)g.size();
    vector<bool> dead(n, false);

    function<void(int)> rec = [&](int start) {
      int c = OneCentroid(start, g, dead);
      dead[c] = true; //重心を切り離す。

      //A:部分木内のだけで、部分木同士独立に行われる処理。

      for (auto u : g[c]) {
        if (!dead[u]) {
          rec(u);
        }
      }

      //B:部分木と重心の間で行われる処理。

      dead[c] = false; //重心を繋げる。バックトラック。
    };
    rec(0);
  }

  //木の重心を１つ以上探す。木の重心の数は高々２つ。
  vector<int> TwoCentroids(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
    static vector<int> sz(g.size());

    function<void(int, int)> get_sz = [&](int u, int prev) {
      sz[u] = 1;
      for (auto v : g[u])
        if (v != prev && !dead[v]) {
          get_sz(v, u);
          sz[u] += sz[v];
        }
    };

    get_sz(root, -1);
    int n = sz[root];
    vector<int> centroid;

    function<void(int, int)> dfs = [&](int u, int prev) {
      bool is_centroid = true;
      for (auto v : g[u])
        if (v != prev && !dead[v]) {
          dfs(v, u);
          if (sz[v] > n / 2) is_centroid = false;
        }
      if (n - sz[u] > n / 2) is_centroid = false;
      if (is_centroid) centroid.push_back(u);
    };

    dfs(root, -1);

    return centroid;
  }
};
