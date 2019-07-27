//距離を求める。

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

//二つの線分の交差判定をする。
bool intersect(Point p1, Point p2, Point p3, Point p4) {
  return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
          ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

bool intersect(Segment s1, Segment s2) {
  return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

//点と点の距離
double getDistance(Point a, Point b) { return (a - b).abs(); }

//点と直線の距離
double getDistanceLP(Line l, Point p) {
  return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}

//点と線分の距離
double getDistanceSP(Segment s, Point p) {
  if (dot(s.p2 - s.p1, p - s.p1) < 0.0)
    return (p - s.p1).abs();
  if (dot(s.p1 - s.p2, p - s.p2) < 0.0)
    return (p - s.p2).abs();
  return getDistanceLP(s, p);
}

//線分と線分の距離
double getDistance(Segment s1, Segment s2) {
  if (intersect(s1, s2))
    return 0.0;
  return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
             min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
