//O(N)
//最小二乗法
//Ｎ個の点を直線の方程式： y=ax+b で近似する。
//N個の点:(v[i].fir,v[i].sec)

pair<double, double> linearApproximation(vector<pair<int, int>> v) {
  int n = v.size();

  double xy = 0, x = 0, y = 0, xx = 0;
  for (int i = 0; i < n; i++) xy += v[i].first * v[i].second;
  for (int i = 0; i < n; i++) x += v[i].first;
  for (int i = 0; i < n; i++) y += v[i].second;
  for (int i = 0; i < n; i++) xx += v[i].first * v[i].first;

  double a = (n * xy - x * y) / (n * xx - x * x);
  double b = (xx * y - xy * x) / (n * xx - x * x);
  return {a, b};
}
