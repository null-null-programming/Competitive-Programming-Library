//O((N+Q)log N)
//直線集合おける最小値（最大値）を求める。

struct CHT {
  vector<P> deq; // y = first * x + second
  int s, t;
  CHT(int n) { //n:クエリ数
    deq.resize(n);
    s = 0, t = 0;
  }

  void add(int a, int b) { //a:単調減少(単調増加)
    const P p(a, b);
    while (s + 1 < t && check(deq[t - 2], deq[t - 1], p)) t--;
    deq[t++] = p;
  }

  int incl_query(int x) { //x：単調増加
    while (s + 1 < t && f(deq[s], x) >= f(deq[s + 1], x)) s++;
    return f(deq[s], x);
  }
  int query(int x) { //条件なし
    int ng = s - 1, ok = t - 1;
    while (abs(ok - ng) > 1) {
      int mid = (ok + ng) / 2;
      if (isright(deq[mid], deq[mid + 1], x)) {
        ng = mid;
      } else {
        ok = mid;
      }
    }
    return f(deq[ok], x);
  }

private:
  bool isright(const P &p1, const P &p2, int x) {
    return (p1.second - p2.second) >= x * (p2.first - p1.first);
  }
  bool check(const P &p1, const P &p2, const P &p3) {
    return (p2.first - p1.first) * (p3.second - p2.second) >= (p2.second - p1.second) * (p3.first - p2.first);
  }
  int f(const P &p, int x) {
    return p.first * x + p.second;
  }
};
