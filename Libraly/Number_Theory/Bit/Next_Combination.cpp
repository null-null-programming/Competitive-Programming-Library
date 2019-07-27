/* next combination */
int next_combination(int sub) {
  int x = sub & -sub, y = sub + x;
  return (((sub & ~y) / x) >> 1) | y;
}

int main() {
  int n; // {0, 1, 2,....n-1}
  int k;

  int bit = (1 << k) - 1; // bit = {0, 1, 2...k}
  for (; bit < (1 << n); bit = next_combination(bit)) {
  }
}
