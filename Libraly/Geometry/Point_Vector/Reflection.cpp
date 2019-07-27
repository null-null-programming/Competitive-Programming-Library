//ある直線/線分に対する、ある点の反射を求める。

//ある点から、直線/線分に対する射影を求める。
Point project(Segment s, Point p) {
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / base.norm();
  return s.p1 + base * r;
}

Point reflect(Segment s, Point p) { return p + (project(s, p) - p) * 2.0; }
