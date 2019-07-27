
class Combination {
private:
  const int MOD;
  vector<int> fac, finv, inv;

  int combination(int n, int k) {
    if (n < k)
      return 0;
    if (n < 0 || k < 0)
      return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
  }

  int permutation(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[n - k] % MOD;
  }

  int homogeneousProduct(int n, int k) { return combination(n + k - 1, k); }

public:
  Combination(int MAX_N, int MOD) : MOD(MOD) {
    fac.resize(MAX_N, 1);
    finv.resize(MAX_N, 1);
    inv.resize(MAX_N, 1);
    for (int i = 2; i < MAX_N; i++) {
      fac[i] = fac[i - 1] * i % MOD;
      inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
      finv[i] = finv[i - 1] * inv[i] % MOD;
    }
  }

  int nCk(int n, int k) { return combination(n, k); }
  int nPk(int n, int k) { return permutation(n, k); }
  int nHk(int n, int k) { return homogeneousProduct(n, k); }
};
