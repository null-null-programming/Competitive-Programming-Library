//O(S)
//SとS[i:|S| - 1]の最長共通接頭辞の大きさを記録した配列を求める。

vector<int> z_algorithm(const string &s) {
  vector<int> prefix(s.size());
  for (int i = 1, j = 0; i < s.size(); i++) {
    if (i + prefix[i - j] < j + prefix[j]) {
      prefix[i] = prefix[i - j];
    } else {
      int k = max(0LL, j + prefix[j] - i);
      while (i + k < s.size() && s[k] == s[i + k]) ++k;
      prefix[i] = k;
      j = i;
    }
  }
  prefix[0] = (int)s.size();
  return prefix;
}
