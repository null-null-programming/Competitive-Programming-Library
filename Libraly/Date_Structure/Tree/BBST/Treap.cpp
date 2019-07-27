//Treap

template <typename T>
class Treap {
private:
  unsigned int rnd() {
    static unsigned int tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
    unsigned int tt = (tx ^ (tx << 11));
    tx = ty;
    ty = tz;
    tz = tw;
    return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
  }

  struct Node {
    T key;
    Node *l, *r;
    int priority;
    int cont;
    T sum;
    T min;

    Node(T key, int priority) : key(key), priority(priority), l(nullptr), r(nullptr), cont(1), sum(sum), min(INF) {}
  } *root = nullptr;

  using Tree = Node *;

  int cont(Node *t) { return !t ? 0 : t->cont; }
  T sum(Node *t) { return !t ? 0 : t->sum; }
  T min(Node *t) { return !t ? 0 : t->min; }

  Tree update(Tree t) {
    t->cont = cont(t->l) + cont(t->r) + 1LL;
    t->sum = sum(t->l) + sum(t->r) + t->key;
    t->min = min(min(t->l), min(t->r));
    return t;
  }

  void split(Tree t, T key, Tree &l, Tree &r) {
    if (!t) {
      l = r = nullptr;
    } else if (key < t->key) {
      split(t->l, key, l, t->l), r = t;
      update(t);
    } else {
      split(t->r, key, t->r, r), l = t;
      update(t);
    }
  }

  void merge(Tree &t, Tree l, Tree r) {
    if (!l || !r) {
      t = l ? l : r;
    } else if (l->priority > r->priority) {
      merge(l->r, l->r, r), t = l;
      update(t);
    } else {
      merge(r->l, l, r->l), t = r;
      update(t);
    }
  }

  void insert(Tree &t, Tree item) {
    if (!t) {
      t = item;
    } else if (item->priority > t->priority) {
      split(t, item->key, item->l, item->r), t = item;
      update(t);
    } else {
      insert(item->key < t->key ? t->l : t->r, item);
      update(t);
    }
  }

  void erase(Tree &t, T key) {
    if (t->key == key) {
      merge(t, t->l, t->r);
      update(t);
    } else {
      erase(key < t->key ? t->l : t->r, key);
      update(t);
    }
  }

  Tree find(Tree &t, T key) {
    if (!t) {
      return nullptr;
    } else if (t->key == key) {
      return t;
    } else {
      return find(key < t->key ? t->l : t->r, key);
    }
  }

  int min(Node *n, int l, int r) {
    l = max(l, 0LL);
    r = min(r, cont(n));
    if (l >= r) return INF;
    if (l == 0 && r == cont(n)) return min(n);
    int res = INF;
    int sl = cont(n->l);
    if (l <= sl && sl < r) res = min(res, n->key);
    res = min(res, min(n->l, l, r));
    res = min(res, min(n->r, l - sl - 1, r - sl - 1));
    return res;
  }

public:
  void insert(T key) { insert(root, new Node(key, rnd())); }
  void erase(T key) { erase(root, key); }
  bool find(T key) { return find(root, key) != nullptr; }
  bool min(int l, int r) { return min(root, l, r); }
};
