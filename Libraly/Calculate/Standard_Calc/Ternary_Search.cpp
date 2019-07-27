//三分探索
//Ｏ(log n)

double f(double x) {
}

double ternarySearch(double l, double r) {
  for (int i = 0; i < 200; i++) {
    double a = (l + l + r) / 3;
    double b = (l + r + r) / 3;
    if (f(a) > f(b)) //f(x)が下に凸のとき「＞」、上に凸のとき「＜」
      l = a;
    else
      r = b;
  }
  return l;
}
