//Ｏ(|E|log|V|)
vector<P> G[MAX_V]; // G[v]=P(w,i):=頂点ｖとiの間の辺の重さがｗ
bool used[MAX_V];   // used[i]=:頂点iをすでに通ったかどうか

int prim() {
  int res = 0; // res=:最小全域木の辺の重さの総和
  priority_queue<P, vector<P>, greater<P>> q;
  memset(used, 0, sizeof(used));

  q.push(P(0, 0));
  while (!q.empty()) {
    P p = q.top();
    q.pop();
    int d = p.first, v = p.second; // first:辺の重さ、second:次の頂点
    if (used[v])
      continue;
    used[v] = 1;
    res += d;
    for (int i = 0; i < (int)G[v].size(); i++) {
      q.push(G[v][i]);
    }
  }
  return res;
}
