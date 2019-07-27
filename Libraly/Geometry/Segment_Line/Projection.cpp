//pからｓへの射影
Point project(Segment s, Point p) {
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / base.norm();
  return s.p1 + base * r;
}
