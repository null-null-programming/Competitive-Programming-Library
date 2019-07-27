const int MAX = 1010100;

// MODが素数でなくてもいい組み合わせ
//１<=k<=n<=2000;
int Com[MAX][MAX];

void calc_com() {
  memset(Com, 0, sizeof(Com));
  Com[0][0] = 1;
  for (int i = 1; i < MAX; i++) {
    Com[i][0] = 1;
    for (int j = 1; j < MAX; j++) {
      Com[i][j] = (Com[i - 1][j - 1] + Com[i - 1][j]) % MOD;
    }
  }
}
/////////////////////////////////////////////
// nが巨大で固定的な時
// 1<=n<=10^9,1<=k<=10^7

int HugeComb[MAX]; //:=HugeComb[k]=nCk
int n;

void Huge_CombInit() {
  HugeComb[0] = 1;
  for (int i = 1; i < MAX; i++) {
    HugeComb[i] = HugeComb[i - 1] * n / (i * (n - i));
  }
}
//////////////////////////////////////////////
//テーブルを作らない
//O(r)

int fact_mod(int n, int mod = MOD) {
  int f = 1;
  for (int i = 2; i <= n; i++) f = f * (i % mod) % mod;
  return f;
}

int mod_pow(int x, int n, int mod = MOD) {
  if (n == 0) return 1;
  int res = mod_pow((x * x) % mod, n / 2, mod);
  if (n & 1) res = (res * x) % mod;
  return res;
}

int nCr(int n, int r, int mod = MOD) {
  if (r > n - r) r = n - r;
  if (r == 0) return 1;
  int a = 1;
  for (int i = 0; i < r; i++) a = a * ((n - i) % mod) % mod;
  int b = mod_pow(fact_mod(r, mod), mod - 2, mod);
  return (a % mod) * (b % mod) % mod;
}
