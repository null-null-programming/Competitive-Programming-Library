//O(N log {max_bi})
//extGcdで連立合同方程式の解を求める。

inline int mod(int a, int m) {
  return (a % m + m) % m;
}

int extGcd(int a, int b, int &p, int &q) {
  if (b == 0) {
    p = 1;
    q = 0;
    return a;
  }
  int d = extGcd(b, a % b, q, p);
  q -= a / b * p;
  return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<int, int> ChineseRem(const vector<int> &b, const vector<int> &m) {
  int r = 0, M = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    int p, q;
    int d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return make_pair(0, -1);
    int tmp = (b[i] - r) / d * p % (m[i] / d);
    r += M * tmp;
    M *= m[i] / d;
  }
  return make_pair(mod(r, M), M);
}
