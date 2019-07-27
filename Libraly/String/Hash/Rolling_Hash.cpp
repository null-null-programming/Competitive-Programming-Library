//Rolling Hash

//不安定ー高速
//mod 2^64　のため衝突する恐れあり
struct RollingHash64 {
  const ull B = 1e9 + 7; //基数

  //aはbにいくつ含まれているか？
  int contain(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;

    //B^al
    ull t = 1;
    for (int i = 0; i < al; i++) t *= B;

    //a,bの最初のal文字のハッシュ
    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) ah = ah * B + a[i];
    for (int i = 0; i < al; i++) bh = bh * B + b[i];

    int cont = 0;
    for (int i = 0; i + al <= bl; i++) {
      if (ah == bh) cont++;
      if (i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return cont;
  }

  //mod 2^64
  //aの末尾とbの先頭を何文字重ねることができるか？
  int overlap(string a, string b) {
    int al = a.length(), bl = b.length();
    int ans = 0;
    ull ah = 0, bh = 0, t = 1;
    for (int i = 1; i <= min(al, bl); i++) {
      ah = ah + a[al - i] * t;
      bh = bh * B + b[i - 1];
      if (ah == bh) ans = i;
      t *= B;
    }
    return ans;
  }
};

//遅すぎる
//６４を使え。
struct RollingHash {
  const ull B = 813297308; //基数　1 ~ M1-1　までの乱数
  const ull M[3] = {999999937, 1000000007, 1000000009};

  //bにaはいくつ含まれているか？
  int contain(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;

    //B^al
    ull t[3];
    for (int i = 0; i < 3; i++) {
      t[i] = 1;
      for (int j = 0; j < al; j++) t[i] = (t[i] * B) % M[i];
    }

    //a,bの最初のal文字のハッシュ
    ull ah[3], bh[3];
    for (int i = 0; i < 3; i++) {
      ah[i] = bh[i] = 0;
      for (int j = 0; j < al; j++) ah[i] = ((ah[i] * B) % M[i] + a[j]) % M[i];
      for (int j = 0; j < al; j++) bh[i] = ((bh[i] * B) % M[i] + b[j]) % M[i];
    }

    int cont = 0;
    for (int i = 0; i + al <= bl; i++) {
      bool flag = true;
      for (int j = 0; j < 3; j++) {
        if (ah[j] != bh[j]) flag = false;
        if (i + al < bl) {
          bh[j] = (bh[j] * B) % M[j] + (b[i + al] - (b[i] * t[j]) % M[j] + M[j]) % M[j];
          bh[j] %= M[j];
        }
      }
      if (flag) cont++;
    }
    return cont;
  }
};
