//O(N^2)
//Garnerのアルゴリズム
//中国剰余定理

inline int mod(int a, int m) {
  int res = a % m;
  if (res < 0) res += m;
  return res;
}

int GCD(int a, int b) {
  if (b == 0)
    return a;
  else
    return GCD(b, a % b);
}

int extGCD(int a, int b, int &p, int &q) {
  if (b == 0) {
    p = 1;
    q = 0;
    return a;
  }
  int d = extGCD(b, a % b, q, p);
  q -= a / b * p;
  return d;
}

int modinv(int a, int m) {
  int x, y;
  extGCD(a, m, x, y);
  return mod(x, m);
}

int PreGarner(vector<int> &b, vector<int> &m, int MOD) {
  int res = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      int g = GCD(m[i], m[j]);
      if ((b[i] - b[j]) % g != 0) return -1;

      m[i] /= g;
      m[j] /= g;
      int gi = GCD(m[i], g), gj = g / gi;

      do {
        g = GCD(gi, gj);
        gi *= g, gj /= g;
      } while (g != 1);

      m[i] *= gi, m[j] *= gj;
      b[i] %= m[i], b[j] %= m[j];
    }
  }

  for (int i = 0; i < (int)b.size(); ++i) (res *= m[i]) %= MOD;
  return res;
}

int Garner(vector<int> b, vector<int> m, int MOD) {
  m.push_back(MOD);
  vector<int> coeffs((int)m.size(), 1);
  vector<int> constants((int)m.size(), 0);
  //m同士で互いに素でない場合があるとき。
  //preGarner(b,m,MOD);
  for (int k = 0; k < (int)b.size(); ++k) {
    int t = mod((b[k] - constants[k]) * modinv(coeffs[k], m[k]), m[k]);
    for (int i = k + 1; i < (int)m.size(); ++i) {
      (constants[i] += t * coeffs[i]) %= m[i];
      (coeffs[i] *= m[k]) %= m[i];
    }
  }
  return constants.back();
}

/*
ex)

signed main() {
  int N;
  cin >> N;
  vec X(N), Y(N);

  bool flag = true;
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
    if (X[i]) flag = false;
  }

  int lcm = PreGarner(X, Y, MOD);
  if (lcm == -1) {
    cout << -1 << endl;
    return 0;
  }
  if (flag) {
    cout << lcm << endl;
    return 0;
  }

  cout << Garner(X, Y, MOD) << endl;
  return 0;
}
*/
