//最長回文の長さを求める。
//O(N)

int Manarcher(const string &_s) {
  int n = _s.size();
  string s(2 * n + 1, '#');
  for (int i = 0; i < n; i++) s[2 * i + 1] = _s[i];
  n = 2 * n + 1;

  vector<int> rad(n);
  for (int i = 0, j = 0; i < n;) {
    while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) j++;
    rad[i] = j;

    int k;
    for (k = 1; i - k >= 0 && rad[i] - k > rad[i - k]; k++) rad[i + k] = rad[i - k];

    i += k;
    j = max(j - k, 0LL);
  }
  return *max_element(rad.begin(), rad.end()) - 1;
}
