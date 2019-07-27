//計算量Ｏ(n logn)
//凸包を求める。

// 3点の位置関係を調べる。

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

int ccw(Point p0, Point p1, Point p2) {
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if (cross(a, b) > EPS)
    return COUNTER_CLOCKWISE;
  if (cross(a, b) < -EPS)
    return CLOCKWISE;
  if (dot(a, b) < -EPS)
    return ONLINE_BACK;
  if (a.norm() < b.norm())
    return ONLINE_FRONT;

  return ON_SEGMENT;
}

Polygon andrewScan(Polygon s) {
  Polygon u, l;
  if (s.size() < 3)
    return s;
  sort(s.begin(), s.end()); // x,yを基準にsort
  //ｘが小さいものから２つ追加
  u.push_back(s[0]);
  u.push_back(s[1]);
  // xが大きいものから２つ追加
  l.push_back(s[s.size() - 1]);
  l.push_back(s[s.size() - 2]);

  //凸包の上部を作成。
  for (int i = 2; i < s.size(); i++) {
    //＜！！！！！注意！！！！！＞凸包の辺上の点も含めるときは↓　！＝を＝＝に変更する。
    for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE;
         n--) {
      u.pop_back();
    }
    u.push_back(s[i]);
  }

  //凸包の下部を作成。
  for (int i = s.size() - 3; i >= 0; i--) {
    //＜！！！！！注意！！！！！＞凸包の辺上の点も含めるときは↓　！＝を＝＝に変更する。
    for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE;
         n--) {
      l.pop_back();
    }
    l.push_back(s[i]);
  }

  //反時計回りになるように凸包の点の列を生成。
  reverse(l.begin(), l.end());
  for (int i = u.size() - 2; i >= 1; i--)
    l.push_back(u[i]);

  return l;
}

//凸包の周長を求める。
double hull_length(Polygon s) {
  double res = 0.0;
  for (auto itr = s.begin();; itr++) {
    if (itr == s.end() - 1) {
      res += (*(itr) - *(s.begin())).abs();
      break;
    }
    res += (*(itr + 1) - *(itr)).abs();
  }

  return res;
}
