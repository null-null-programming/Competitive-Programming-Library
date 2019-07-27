//遅延セグメント木
//区間更新、区間取得

//動作未確認！！！！！！！！！！

struct LazySegmentTree_SST {
  int n;
  vector<int> dat, lazy;

  //初期化
  void init(int n_) {
    n = 1;
    while (n < n_) n *= 2;
    dat.resize(2 * n - 1, INF);
    lazy.resize(2 * n - 1, 0);
  }

  void eval(int k, int l, int r) {
    //遅延配列が空でない場合、値の伝播を行う。
    if (lazy[k] != 0) {
      dat[k] += lazy[k];

      //最下段ではないかチェック
      if (r - l > 1) {
        //区間が半分なので、半割して伝播する
        lazy[2 * k + 1] += lazy[k] / 2;
        lazy[2 * k + 2] += lazy[k] / 2;
      }

      //伝播後、自ノードを空にする
      lazy[k] = 0;
    }
  }

  //区間[a,b)に対して一様にxを足す。
  //呼び出し方：add(a,b,x);
  void update(int a, int b, int x, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;

    //ｋ番目のノードに対して遅延評価する。
    eval(k, l, r);

    //範囲外なのでなにもしない。
    if (b <= l || r <= a) return;

    //完全に被覆している場合、遅延配列に加算した後に評価する
    if (a <= l && r <= b) {
      lazy[k] += (r - l) * x;
      eval(k, l, r);
    }

    //一部被覆している場合子ノードを再帰的に計算し
    //計算済みの値を用いて、自ノードを更新する
    else {
      update(a, b, x, 2 * k + 1, l, (l + r) / 2);
      update(a, b, x, 2 * k + 2, (l + r) / 2, r);
      dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  int query(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (r <= a || b <= l) return INF;

    //関数が呼び出されたので評価する。
    eval(k, l, r);
    if (a <= l && r <= b) return dat[k];

    int vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    int vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(vl, vr);
  }
};
