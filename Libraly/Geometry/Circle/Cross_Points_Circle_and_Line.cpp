//円と直線の交点を求める。

double getDistanceLP(Line l, Point p) {
  return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}

bool intersect(Circle c, Line l) {
  if (getDistanceLP(l, c.c) > c.r)
    return false;
  return true;
}

//ある点から、直線/線分に対する射影を求める。
Point project(Segment s, Point p) {
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / base.norm();
  return s.p1 + base * r;
}

pair<Point, Point> getCrossPoints(Circle c, Line l) {
  assert(intersect(c, l));
  Vector pr = project(l, c.c);
  Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
  double base = sqrt(c.r * c.r - (pr - c.c).norm());
  return make_pair(pr + e * base, pr - e * base);
}
