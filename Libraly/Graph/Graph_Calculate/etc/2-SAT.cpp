//O(N)
//充足可能性問題を解く。

//O(V+E)
//強連結成分分解
const int MAX_V = ;

int V;                 //頂点数
vector<int> G[MAX_V];  //グラフの辺
vector<int> rG[MAX_V]; //逆向きの辺
vector<int> vs;        //帰りがけ順の並び
bool used[MAX_V];      //既に調べたかどうか
int cmp[MAX_V];        //属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    if (!used[G[v][i]]) dfs(G[v][i]);
  }
  vs.push_back(v);
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  for (int i = 0; i < rG[v].size(); i++) {
    if (!used[rG[v][i]]) rdfs(rG[v][i], k);
  }
}

int scc() {
  memset(used, 0, sizeof(used));
  vs.clear();
  for (int v = 0; v < V; v++) {
    if (!used[v]) dfs(v);
  }
  memset(used, 0, sizeof(used));
  int k = 0;
  for (int i = vs.size() - 1; i >= 0; i--) {
    if (!used[vs[i]]) rdfs(vs[i], k++);
  }
  return k; //scc後の頂点数
}

int N; //リテラルの要素数。

void solve() {
  V = 2 * N;
  //各リテラルをxで表す。対応は以下の通り
  //0~N-1  :  x_i
  //N~2*N-1: ￢x_i

  //以下xリテラルの入力
  /*
  //入力例：
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (max(L[i], L[j]) <= min(L[i] + D[i], L[j] + D[j])) {
        add_edge(i + N, j);
        add_edge(j + N, i);
      }
      if (max(R[i], R[j]) <= min(R[i] + D[i], R[j] + D[j])) {
        add_edge(i, j + N);
        add_edge(j, i + N);
      }
      if (max(R[i], L[j]) <= min(R[i] + D[i], L[j] + D[j])) {
        add_edge(i, j);
        add_edge(j + N, i + N);
      }
      if (max(L[i], R[j]) <= min(L[i] + D[i], R[j] + D[j])) {
        add_edge(j, i);
        add_edge(i + N, j + N);
      }
    }
  }
  */

  //強連結成分分解
  int k = scc();

  for (int i = 0; i < N; i++) {
    if (cmp[i] == cmp[N + i]) {
      //cout << "NO" << endl;
      return;
    }
  }

  //cout<<"Yes"<<endl;

  for (int i = 0; i < N; i++) {
    if (cmp[i] > cmp[i + N]) {
      //cout<<"true"<<endl;   x_iは真である。
    } else {
      //cout<<"false"<<endl;  x_iは偽である。
    }
  }
}
