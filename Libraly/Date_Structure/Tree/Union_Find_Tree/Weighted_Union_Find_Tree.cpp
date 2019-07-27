

template <class Abel>
class WUnionFind {
private:
  vector<int> par;
  vector<int> rank;
  vector<Abel> diff_weight;

  void init(int n = 1, Abel SUM_UNITY = 0) {
    par.resize(n);
    rank.resize(n);
    diff_weight.resize(n);
    for (int i = 0; i < n; i++) {
      par[i] = i, rank[i] = 0, diff_weight[i] = SUM_UNITY;
    }
  }

  int get_root(int x) {
    if (par[x] == x) {
      return x;
    } else {
      int r = root(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = r;
    }
  }

  Abel get_weight(int x) {
    root(x);
    return diff_weight[x];
  }

  bool is_same(int x, int y) {
    return root(x) == root(y);
  }

  bool do_unit(int x, int y, Abel w) {
    w += weight(x);
    w -= weight(y);

    x = root(x), y = root(y);
    if (x == y) return false;
    if (rank[x] < rank[y]) swap(x, y), w = -w;
    if (rank[x] == rank[y]) rank[x]++;
    par[y] = x;
    diff_weight[y] = w;
    return true;
  }

  Abel get_diff(int x, int y) {
    return weight(y) - weight(x);
  }

public:
  WUnionFind(int n = 1, Abel SUM_UNITY = 0) {
    init(n, SUM_UNITY);
  }

  int root(int x) { return get_root(x); }
  Abel weight(int x) { return get_weight(x); }
  bool same(int x, int y) { return is_same(x, y); }
  bool unite(int x, int y) { return unite(x, y); }
  int diff(int x, int y) { return get_diff(x, y); }
};
