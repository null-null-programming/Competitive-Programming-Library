//O(N log N)

int inversion_number(vector<int> &a) {
  int n = a.size();
  if (n <= 1) return 0;

  vector<int> b(a.begin(), a.begin() + n / 2);
  vector<int> c(a.begin() + n / 2, a.end());

  int cont = 0;
  cont += inversion_number(b);
  cont += inversion_number(c);

  int ai = 0, bi = 0, ci = 0;
  while (ai < n) {
    if (bi < b.size() && (ci == c.size() || b[bi] <= c[ci])) {
      a[ai++] = b[bi++];
    } else {
      cont += n / 2 - bi;
      a[ai++] = c[ci++];
    }
  }

  return cont;
}
