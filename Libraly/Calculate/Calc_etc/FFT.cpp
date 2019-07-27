//O(N log N)
//FFT(高速フーリエ変換)
//・答えとなる配列の大きさは２＾tの形でなければならない。
//・(f*g)(x)=IDFT(DFT(f)*DFT(g))の形で使う

// 高速逆フーリエ変換
const Complex I(0, 1);

//inverse:1 ->dft
//inverse:-1->idft

//注意点：Nは２の累乗である必要がある
void fft(Complex a[], int n, int inverse) {
  double theta = 2 * inverse * M_PI / n;

  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      Complex w = exp(i * theta * I);
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        Complex x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta *= 2;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1)
      ;
    if (j < i) swap(a[i], a[j]);
  }

  if (inverse == -1) {
    Complex d(n, 0);
    for (int i = 0; i < n; i++) {
      a[i] = a[i] / d;
    }
  }
}
/*使用例
signed main() {
  int N;
  cin >> N;

  int n = 1;
  while (n < 2 * N) n *= 2;

  static int a[202020], b[202020];
  for (int i = 0; i < N; i++) {
    cin >> a[i] >> b[i];
  }

  Complex *gg = new Complex[n];
  Complex *hh = new Complex[n];

  for (int i = 0; i < n; i++) {
    if (i < N) {
      gg[i] = a[i];
      hh[i] = b[i];

    } else {
      gg[i] = 0;
      hh[i] = 0;
    }
  }

  fft(gg, n, 1);
  fft(hh, n, 1);

  static Complex f[202020];
  for (int i = 0; i < n; i++) {
    f[i] = gg[i] * hh[i];
  }

  fft(f, n, -1);

  cout << 0 << endl;
  for (int i = 0; i < 2 * N - 1; i++) {
    cout << (int)(f[i].real() + 0.5) << endl;
  }

  return 0;
}
*/
