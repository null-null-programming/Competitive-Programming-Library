//O(V+E)
//二部グラフかどうかを判定する。
//戻り値は片側の要素数
//ただし、二部グラフでない場合は-1を返す。

int IsBipartiteGraph(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> color(n, -1);
  int white_cnt = 0;
  function<bool(int, int, int)> dfs = [&](int u, int prev, int c) {
    color[u] = c;
    if (c == 1) white_cnt++;
    for (auto v : g[u])
      if (v != prev) {
        if (color[v] == -1) {
          if (!dfs(v, u, 1 - c)) return false;
        } else if (color[v] != 1 - c) {
          return false;
        }
      }
    return true;
  };
  if (!dfs(0, -1, 0)) return -1;
  return white_cnt;
}
