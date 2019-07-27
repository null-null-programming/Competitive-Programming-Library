class UnionFind {
private:
  vector<int> data;

  bool isSame(int x, int y) {
    return find(x) == find(y);
  }

  bool doUnite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return (false);
    if (data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }

  int getFind(int k) {
    if (data[k] < 0) return (k);
    return (data[k] = find(data[k]));
  }

  int getSize(int k) {
    return (-data[find(k)]);
  }

public:
  UnionFind(int N) {
    data.resize(N, -1);
  }

  int same(int x, int y) { return isSame(x, y); }
  bool unite(int x, int y) { return doUnite(x, y); }
  int find(int k) { return getFind(k); }
  int size(int k) { return getSize(k); }
};
