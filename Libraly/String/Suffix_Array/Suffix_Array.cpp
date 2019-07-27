
//Suffix Array
//build:  O(n log^2 n)
//ub,lb:  O(log n)

struct SuffixArray {
  int n, k;
  vector<int> rank, rank_, tmp;

  SuffixArray(const int &n_, const string &s, int *sa) {
    rank.resize(n_), rank_.resize(n_), tmp.resize(n_);
    sa_construct(s, sa);
  }
  SuffixArray(const int &n_, const string &s, int *sa, int *lcp) {
    rank.resize(n_), rank_.resize(n_), tmp.resize(n_);
    sa_construct(s, sa);
    lcp_construct(s, sa, lcp);
  }

  void sa_construct(const string &s, int *sa) {
    n = s.length();

    for (int i = 0; i <= n; i++) {
      sa[i] = i;
      rank_[i] = i < n ? s[i] : -1;
    }

    auto compare_sa = [&](int i, int j) {
      if (rank_[i] != rank_[j])
        return rank_[i] < rank_[j];
      else {
        int ri = i + k <= n ? rank_[i + k] : -1LL;
        int rj = j + k <= n ? rank_[j + k] : -1LL;
        return ri < rj;
      }
    };

    for (k = 1; k <= n; k *= 2) {
      sort(sa, sa + n + 1, [&](int i, int j) { return compare_sa(i, j); });

      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; i++) {
        tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
      }
      for (int i = 0; i <= n; i++) {
        rank_[i] = tmp[i];
      }
    }
  }

  void lcp_construct(const string &s, int *sa, int *lcp) {
    n = s.length();
    for (int i = 0; i <= n; i++) rank[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
      int j = sa[rank[i] - 1];

      if (h > 0) h--;
      for (; j + h < n && i + h < n; h++) {
        if (s[j + h] != s[i + h]) break;
      }

      lcp[rank[i] - 1] = h;
    }
  }

  //lower_bound
  int lb(const string &S, const string &T, int *sa) {
    int a = 0, b = S.length() + 1;
    while (abs(a - b) > 1) {
      int c = (a + b) / 2;
      if (S.compare(sa[c], T.length(), T) < 0)
        a = c;
      else
        b = c;
    }
    return b;
  }
  //upper_bound
  int ub(const string &S, const string &T, int *sa) {
    int a = 0, b = S.length() + 1;
    while (abs(a - b) > 1) {
      int c = (a + b) / 2;
      if (S.compare(sa[c], T.length(), T) <= 0)
        a = c;
      else
        b = c;
    }
    return b;
  }
  //binary_count
  int count(const string &S, const string &T, int *sa) {
    return ub(S, T, sa) - lb(S, T, sa);
  }
};
