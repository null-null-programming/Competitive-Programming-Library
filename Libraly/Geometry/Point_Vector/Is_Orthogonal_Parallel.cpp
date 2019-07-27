//直交判定
bool isOrthogonal(Vector a, Vector b) { return equals(dot(a, b), 0.0); }

bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
  return isOrthogonal(a1 - a2, b1 - b2);
}

bool isOrthogonal(Segment s1, Segment s2) {
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

//平行判定
bool isParallel(Vector a, Vector b) { return equals(cross(a, b), 0.0); }

bool isParallel(Point a1, Point a2, Point b1, Point b2) {
  return isParallel(a1 - a2, b1 - b2);
}

bool isParallel(Segment s1, Segment s2) {
  return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
