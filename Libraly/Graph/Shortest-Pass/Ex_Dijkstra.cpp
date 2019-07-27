//O(E log E)
//拡張ダイクストラ

struct edge {
  int to, cost;
};

const int S_MAX = 1000;

int N, M, S;
vector<edge> G[101010];

int dist[S_MAX][101010]; //dp[s][n]:=残りチケットがｓ枚のとき、nまでの最短距離

void dijkstra() {
  typedef pair<int, P> T; //pair<頂点までの最短距離、P(残りチケット、頂点)＞:=T(d,s,v)
  priority_queue<T, vector<T>, greater<T>> que;
  que.push(T(0, P(S, 0)));

  while (!que.empty()) {
    T t = que.top();
    que.pop();
    int d = t.first, s = t.second.first, v = t.second.second;

    if (d > dist[s][v]) continue;

    //not use
    for (auto e : G[v]) {
      if (dist[s][e.to] > d + e.cost) {
        dist[s][e.to] = d + e.cost;
        que.push(T(dist[s][e.to], P(s, e.to)));
      }
    }

    //use
    if (s >= 1) {
      for (auto e : G[v]) {
        if (dist[s - 1][e.to] > d) {
          dist[s - 1][e.to] = d;
          que.push(T(dist[s - 1][e.to], P(s - 1, e.to)));
        }
      }
    }
  }
}
