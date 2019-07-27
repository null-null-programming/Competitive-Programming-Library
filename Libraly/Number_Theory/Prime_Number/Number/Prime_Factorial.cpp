//O(√n)
map<int, int> prime_factor(int n) {
  map<int, int> res;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) {
        res[i]++;
        n /= i;
      }
    }
  }
  if (n != 1)
    res[n] = 1;
  return res;
}
