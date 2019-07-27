//遅延セグメント木
//区間更新、区間取得ＲMＱ

struct LazySegmentTree_RMQ {
  int n;
  vector<int> dat, lazy;
  vector<bool> lazyFlag; //区間更新用flag

  //初期化
  void init(int n_) {
    n = 1;
    while (n < n_) n *= 2;
    dat.resize(2 * n - 1, INF);
    lazy.resize(2 * n - 1, INF);
    lazyFlag.resize(2 * n - 1, false);
  }

  void eval(int k, int l, int r) {
    if (lazyFlag[k]) {
      dat[k] = lazy[k];
      if (r - l > 1) {
        lazy[2 * k + 1] = lazy[2 * k + 2] = lazy[k];
        lazyFlag[2 * k + 1] = lazyFlag[k * 2 + 2] = true;
      }
      lazyFlag[k] = false;
    }
  }

  //呼び出し方：add(a,b,x);
  void update(int a, int b, int x, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    eval(k, l, r);
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      lazy[k] = x;
      lazyFlag[k] = true;
      eval(k, l, r);
    }

    else {
      update(a, b, x, 2 * k + 1, l, (l + r) / 2);
      update(a, b, x, 2 * k + 2, (l + r) / 2, r);
      dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  int query(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    eval(k, l, r);
    if (r <= a || b <= l) return INF;
    if (a <= l && r <= b) return dat[k];

    int vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    int vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(vl, vr);
  }
};
