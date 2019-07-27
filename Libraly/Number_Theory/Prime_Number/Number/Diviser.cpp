//Ｏ(√ｎ)
//約数の列挙
vector<int> diviser(int n) {
  vector<int> res;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.push_back(i);
      if (i != n / i)
        res.push_back(n / i);
    }
  }
  return res;
}
