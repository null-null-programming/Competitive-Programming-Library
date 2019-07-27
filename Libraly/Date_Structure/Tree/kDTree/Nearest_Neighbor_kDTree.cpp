int N, L;

inline double dist(double x1, double y1, double x2, double y2) {
  return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

struct data {
  int index;
  vector<double> v;
  data(int _d) : v(_d) {}
  data() {}
};

struct vertex {
  data val;
  vertex *left;
  vertex *right;
};

class axisSorter {
  int k;

public:
  axisSorter(int _k) : k(_k) {}
  double operator()(const data &a, const data &b) {
    return a.v[k] < b.v[k];
  }
};

vertex *makeKDTree(vector<data> &xs, int l, int r, int depth) {
  if (l >= r)
    return NULL;

  sort(xs.begin() + l, xs.begin() + r, axisSorter(depth % xs[0].v.size()));
  int mid = (l + r) >> 1;

  vertex *v = new vertex();
  v->val = xs[mid];
  v->left = makeKDTree(xs, l, mid, depth + 1);
  v->right = makeKDTree(xs, mid + 1, r, depth + 1);

  return v;
}

inline double dist(const data &x, const data &y) {
  double ret = 0;
  for (int i = 0; i < (int)x.v.size(); i++)
    ret += (x.v[i] - y.v[i]) * (x.v[i] - y.v[i]);
  return ret;
}

inline double sq(double x) {
  return x * x;
}

data query(data &a, vertex *v, int depth) {
  int k = depth % a.v.size();
  if ((v->left != NULL && a.v[k] < v->val.v[k]) ||
      (v->left != NULL && v->right == NULL)) {
    data d = query(a, v->left, depth + 1);
    if (dist(v->val, a) < dist(d, a))
      d = v->val;
    if (v->right != NULL && sq(a.v[k] - v->val.v[k]) < dist(d, a)) {
      data d2 = query(a, v->right, depth + 1);
      if (dist(d2, a) < dist(d, a))
        d = d2;
    }
    return d;
  } else if (v->right != NULL) {
    data d = query(a, v->right, depth + 1);
    if (dist(v->val, a) < dist(d, a))
      d = v->val;
    if (v->left != NULL && sq(a.v[k] - v->val.v[k]) < dist(d, a)) {
      data d2 = query(a, v->left, depth + 1);
      if (dist(d2, a) < dist(d, a))
        d = d2;
    }
    return d;
  } else
    return v->val;
}

signed main() {
  int N;
  cin >> N;
  vector<data> xs(N, data(2));
  for (int i = 0; i < N; i++) {
    xs[i].index = i;
    cin >> xs[i].v[0] >> xs[i].v[1];
  }

  vertex *root = makeKDTree(xs, 0, N, 0);

  return 0;
}
