//MODint
template <typename T, T Modulus = 1000000007>
struct Mint {
  T v;
  Mint() : v(0) {}
  Mint(long long t) {
    v = t % Modulus;
    if (v < 0) v += Modulus;
  }

  Mint pow(long long k) {
    Mint res(1), tmp(v);
    while (k) {
      if (k & 1) res *= tmp;
      tmp *= tmp;
      k >>= 1;
    }
    return res;
  }

  Mint inv() { return pow(Modulus - 2); }

  Mint &operator+=(Mint a) {
    v += a.v;
    if (v >= Modulus) v -= Modulus;
    return *this;
  }
  Mint &operator-=(Mint a) {
    v += Modulus - a.v;
    if (v >= Modulus) v -= Modulus;
    return *this;
  }
  Mint &operator*=(Mint a) {
    v = 1LL * v * a.v % Modulus;
    return *this;
  }
  Mint &operator/=(Mint a) { return (*this) *= a.inv(); }
  Mint operator+(Mint a) const { return Mint(v) += a; };
  Mint operator-(Mint a) const { return Mint(v) -= a; };
  Mint operator*(Mint a) const { return Mint(v) *= a; };
  Mint operator/(Mint a) const { return Mint(v) /= a; };
  Mint operator-() { return v ? Modulus - v : v; }
  bool operator==(const Mint a) const { return v == a.v; }
  bool operator!=(const Mint a) const { return v != a.v; }
  bool operator<(const Mint a) const { return v < a.v; }
};
