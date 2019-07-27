//O(N)
class EulerTour {
public:
  int n, k;
  vector<int> eulerTour;
  vector<int> begin, end; // [begin, end)

  // 頂点vを根とする木gのオイラーツアー
  EulerTour(const vector<vector<int>> &g, int v = 0) : n(g.size()), k(0) {
    begin.resize(n, 0);
    end.resize(n, 0);
    createEulerTour(g, v, -1);
  }

  // 頂点vを根とする木gのオイラーツアーを構成する
  void createEulerTour(const vector<vector<int>> &g, int v, int par) {
    begin[v] = k++;
    eulerTour.push_back(v);
    for (auto to : g[v]) {
      if (to == par) continue;
      createEulerTour(g, to, v);
      eulerTour.push_back(v);
      k++;
    }
    end[v] = k;
  }
};
