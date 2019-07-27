//逆元
int mod_inv(int a, int m) {
  int b = m, u = 1, v = 0;
  while (b) {
    int t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}

////////////////////////////////////////////////////
//累乗
int mod_pow(int x, int n, int m) {
  if (n == 0)
    return 1;
  int res = mod_pow(x * x % m, n / 2, m);
  if (n % 2 == 1)
    res = res * x % m;
  return res;
}

/////////////////////////////////////////////////////
//離散対数
//a^x ≡ b (mod. m) となる最小の正の整数 xを計算する。
int mod_log(int a, int b, int m) {
  a %= m, b %= m;

  int ng = -1, ok = m;
  while (abs(ok - ng) > 1) {
    int mid = (ok + ng) / 2;
    if (mid * mid >= m) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  int sqrtM = ok;

  map<int, int> apow;
  int amari = 1;
  for (int r = 0; r < sqrtM; r++) {
    if (!apow.count(amari)) apow[amari] = r;
    (amari *= a) %= m;
  }

  int A = mod_pow(mod_inv(a, m), sqrtM, m);
  amari = b;
  for (int q = 0; q < sqrtM; q++) {
    if (apow.count(amari)) {
      int res = q * sqrtM + apow[amari];
      if (res > 0) return res;
    }
    (amari *= A) %= m;
  }

  return -1;
}

/////////////////////////////////////////////////////
//階乗
const int MAX = 505050;
int fac[MAX], finv[MAX], inv[MAX];
void fact_Init() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < MAX; i++) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

/////////////////////////////////////////////////////
//巨大数剰余
int mod_rem(string n, int MOD) {
  int res = (n[0] - '0') % MOD;
  for (int i = 1; i < n.size(); i++) {
    res = (res * 10 + (n[i] - '0')) % MOD;
  }
  return res;
}
