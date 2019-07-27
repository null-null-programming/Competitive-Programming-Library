//Ｏ(|E|log|V|)
struct edge {
  int u, v, cost;
}; //辺e(u,v)のコストcost

bool comp(const edge &e1, const edge &e2) { return e1.cost < e2.cost; }

edge es[MAX_E];
int V, E; //頂点数、辺数

int par[MAX_E];
int rank_[MAX_E];

//ここからUnion-Find

// n要素で初期化
void init_union_find(int n) {
  for (int t = 0; t < n; t++) {
    par[t] = t;
    rank_[t] = 0;
  }
}

//木の根を求める。
int find(int x) {
  if (par[x] == x) {
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

// xとｙの集合を併合。
void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y)
    return;

  if (rank_[x] < rank_[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank_[x] == rank_[y])
      rank_[x]++;
  }
}

// xとｙが同じ集合に属するかどうか。
bool same(int x, int y) { return find(x) == find(y); }

//ここからKruskal

int kruskal() {
  sort(es, es + E, comp); // edge.costが小さい順にsortする
  init_union_find(V);     // Union-Findの初期化
  int res = 0;            // res:集合Ｘの辺の総和

  for (int i = 0; i < E; i++) {
    edge e = es[i];
    if (!same(e.u, e.v)) {
      unite(e.u, e.v);
      res += e.cost;
    }
  }
  return res;
}
