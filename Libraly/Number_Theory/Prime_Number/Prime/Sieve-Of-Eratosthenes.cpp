class Sieve {
private:
  int prime_num;     // N以下の素数の個数
  vector<int> prime; // i番目の素数
  vector<bool> is_prime;

public:
  Sieve(int N) {
    prime.resize(N);
    is_prime.resize(N + 1);

    prime_num = 0;
    for (int t = 0; t <= N; t++)
      is_prime[t] = true;
    is_prime[0] = is_prime[1] = false;
    for (int t = 2; t <= N; t++) {
      if (is_prime[t] == true) {
        prime[prime_num++] = t;
        for (int i = 2 * t; i <= N; i += t)
          is_prime[i] = false;
      }
    }
  }

  int getPrimeNum(int n) { return prime_num; }
  int getKthPrime(int k) { return prime[k]; }
  bool isPrime(int n) { return is_prime[n]; }
};
