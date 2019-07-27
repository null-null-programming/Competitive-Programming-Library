//二つの線分の交差判定をする。

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

double getDistanceLP(Line l, Point p) {
  return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}

double getDistance(Point a, Point b) { return (a - b).abs(); }

bool intersect(Point p1, Point p2, Point p3, Point p4) {
  return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
          ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

bool intersect(Segment s1, Segment s2) {
  return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

bool intersect(Circle c, Line l) {
  if (getDistanceLP(l, c.c) > c.r)
    return false;
  return true;
}

bool intersect(Circle c1, Circle c2) {
  double d = getDistance(c1.c, c2.c);
  double sum_r = c1.r + c2.r;
  if (d > sum_r)
    return false;
  return true;
}
