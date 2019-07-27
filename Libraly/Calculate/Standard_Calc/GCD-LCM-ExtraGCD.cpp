//Ｏ(log(max(a,b))
// aとbの最大公約数
int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

// aとbの最小公倍数
int lcm(int a, int b) {
  int x = gcd(a, b);
  return (a / x) * b;
}

// ax+by=gcd(a,b)の解、(x,y)を求める。返り値はgcd(a,b)
int extgcd(int a, int b, int &x, int &y) {
  int d = a;
  if (b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}
