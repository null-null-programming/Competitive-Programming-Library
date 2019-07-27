//Ｏ(m^3 log n)
//m項間漸化式の場合

using vec = vector<int>;
using mat = vector<vector<int>>;

//A*Bの計算
mat mul(mat &A, mat &B) {
  mat C(A.size(), vec(B[0].size()));

  for (int i = 0; i < A.size(); i++) {
    for (int k = 0; k < B.size(); k++) {
      for (int j = 0; j < B[0].size(); j++) {
        C[i][j] = (C[i][j] + (A[i][k] * B[k][j])); //<-演算子＋と＊は、演算子xorとandのように半環をなす場合、変更可能。
      }
    }
  }
  return C;
}

//A^nの計算。
mat pow(mat A, int n) {
  mat B(A.size(), vec(A.size()));

  for (int i = 0; i < B.size(); i++) {
    B[i][i] = 1; //<-演算子を変更する場合は、*に対応する方の演算子の単位元とする。andなら-1
  }
  while (n > 0) {
    if (n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}
