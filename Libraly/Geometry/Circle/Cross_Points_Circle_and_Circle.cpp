//円と円の交点を求める。

bool intersect(Circle c1, Circle c2) {
  double d = (c1.c - c2.c).abs();
  double sum_r = c1.r + c2.r;
  if (d > sum_r)
    return false;
  return true;
}

pair<Point, Point> gecCrossPoints(Circle c1, Circle c2) {
  assert(intersect(c1, c2));
  double d = (c1.c - c2.c).abs();
  double a = acos(c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
  double t = arg(c2.c - c1.c);
  return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}
