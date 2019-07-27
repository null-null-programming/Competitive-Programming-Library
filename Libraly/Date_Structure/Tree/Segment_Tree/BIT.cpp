template <typename T>
class BIT {
public:
  int num;
  vector<T> dat;

  //N:1-indexd
  BIT(int N, T val) : num(N) {
    dat.resize(N);
    fill(dat.begin(), dat.end(), val);
  }

  int query(int i) {
    int res = 0;
    while (i > 0) {
      res += dat[i];
      i -= i & -i;
    }
    return res;
  }

  void update(int i, T x) {
    while (i <= num) {
      dat[i] += x;
      i += i & -i;
    }
  }
};
