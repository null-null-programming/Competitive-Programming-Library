//O(√n)
int euler_phi(int n) {
  int res = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      res = res / i * (i - 1);
      for (; n % i == 0; n /= i)
        ;
    }
  }
  if (n != 1) res = res / n * (n - 1);
  return res;
}
//O(n);
vector<int> euler_phi_table(int n) {
  vector<int> res(n);
  for (int i = 0; i < n; i++) res[i] = i;
  for (int i = 2; i < n; i++) {
    if (res[i] == i) {
      for (int j = i; j < n; j += i) {
        res[j] = res[j] / i * (i - 1);
      }
    }
  }
  return res;
}
