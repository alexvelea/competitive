//Problem echipe from Infoarena
#include <cmath>
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
ifstream fin("echipe.in");
ofstream fout("echipe.out");
 
const int INF = 1 << 30;
const int MAX_N = 260;
 
int N, K;
int A[MAX_N], B[MAX_N];
int d[MAX_N][MAX_N];
 
int solve0(), solve1();
 
int main() {
  fin >> N >> K;
  for (int i = 1; i <= N; i += 1) {
    fin >> A[i] >> B[i];
  }
 
  fout << max(solve0(), solve1());
 
  return 0;
}
 
int solve0() {
  vector<int> ls;
  for (int i = 1; i <= N; i += 1) {
    ls.push_back(B[i] - A[i]);
  }
  sort(ls.begin(), ls.end(), greater<int>());
  int result = 0;
  for (int i = 0; i < K - 1; i += 1) {
    result += ls[i];
  }
  return result;
}
 
int solve1() {
  vector<bool> large(N + 1, 0);
  for (int i = 1; i <= N; i += 1) {
    for (int j = i + 1; j <= N; j += 1) {
      if (A[i] <= A[j] && B[i] >= B[j]) large[i] = true;
      if (A[j] <= A[i] && B[j] >= B[i]) large[j] = true;
    }
  }
 
  vector<pair<int, int>> abmin;
  for (int i = 1; i <= N; i += 1) {
    if (!large[i]) abmin.push_back(make_pair(A[i], B[i]));
  }
  sort(abmin.begin(), abmin.end());
  int n = abmin.size();
 
  for (int i = 1; i <= n; i += 1) {
    if (abmin[0].second > abmin[i - 1].first) {
      d[1][i] = abmin[0].second - abmin[i - 1].first;
    }
  }
 
  for (int k = 1; k < K; k += 1) {
    for (int i = 0; i <= n; i += 1) {
      for (int j = i + 1; j <= n; j += 1) {
        if (i > 0 && d[k][i] == 0) continue;
        if (abmin[i].second <= abmin[j - 1].first) continue;
        d[k + 1][j] = max(d[k + 1][j], d[k][i] + abmin[i].second - abmin[j - 1].first);
      }
    }
  }
 
  vector<int> lsp;
  for (int i = 1; i <= N; i += 1) {
    if(large[i]) lsp.push_back(B[i] - A[i]);
  }
  sort(lsp.begin(), lsp.end(), greater<int>());
 
  for (int i = 1; i < int(lsp.size()); i += 1) {
    lsp[i] += lsp[i - 1];
  }
 
  int result = d[K][n];
  for (int i = 1; i < min(K, int(lsp.size())); i += 1) {
    result = max(result, d[K - i][n] + lsp[i - 1]);
  }
  return result;
}
