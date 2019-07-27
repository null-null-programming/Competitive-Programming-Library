//前処理Ｏ(n)
//クエリ処理Ｏ(log n)
//与えられた区間内の「最小値」を求める。

struct SegmentTree {
  int n;
  vector<int> dat;

  void init(int n_) {
    n = 1;
    while (n < n_) n *= 2;
    dat.resize(2 * n - 1, INF);
  }

  void update(int k, int a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  int query(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (r <= a || b <= l) return INF;
    if (a <= l && r <= b) return dat[k];

    int vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    int vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(vl, vr);
  }
};
