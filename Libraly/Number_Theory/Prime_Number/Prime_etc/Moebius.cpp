//O(√n)
//ｎの約数におけるメビウス関数の値をmapで返す。
map<int, int> moebius(int n) {
  map<int, int> res;
  vector<int> primes;

  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      primes.push_back(i);
      while (n % i == 0) n /= i;
    }
  }

  if (n != 1) primes.push_back(n);

  int m = primes.size();
  for (int i = 0; i < (1 << m); i++) {
    int mu = 1, d = 1;
    for (int j = 0; j < m; j++) {
      if ((i >> j) & 1) {
        mu *= -1;
        d *= primes[j];
      }
    }
    res[d] = mu;
  }
  return res;
}
