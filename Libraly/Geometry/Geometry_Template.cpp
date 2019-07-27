//幾何学テンプレート

#define equals(a, b) (fabs((a) - (b)) < EPS)

//点
class Point {
public:
  double x, y;

  Point(double x = 0, double y = 0) : x(x), y(y){};

  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double a) { return Point(a * x, a * y); }
  Point operator/(double a) { return Point(x / a, y / a); }

  double abs() { return sqrt(norm()); }
  double norm() { return x * x + y * y; }

  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator>(const Point &p) const { return x != p.x ? x > p.x : y > p.y; }
  bool operator==(const Point &p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};

//ベクトル
typedef Point Vector;

double norm(Vector a) { return a.x * a.x + a.y * a.y; }
double abs(Vector a) { return sqrt(norm(a)); }
//内積
double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
//外積
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
//角度
double arg(Vector p) { return atan2(p.y, p.x); }
double arg2(Vector p, Vector q) { return acos(dot(p, q) / (abs(p) * abs(q))); }
//極座標:原点からの距離a,角度r[rad]
Vector polar(double a, double r) { return Point(cos(r) * a, sin(r) * a); }
//回転:r倍、angle[rad]回転
Vector rotate(Vector v, double r, double angle) {
  return Vector((cos(angle) - sin(angle)) * v.x * r,
                (sin(angle) - cos(angle)) * v.y * r);
}

//線分
struct Segment {
  Point p1, p2;
};

//直線
typedef Segment Line;

//円
class Circle {
public:
  Point c;  //中心
  double r; //半径
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};

//多角形
typedef vector<Point> Polygon;
