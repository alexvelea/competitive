#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("xnumere.in");
ofstream fout("xnumere2.out");

typedef long long int64;
typedef vector<vector<int>> Matrix;

const int64 MAX_N = 1e15 + 10;
const int MAX_K = 105;
const int MOD = 666013;

int64 K, X, N;

Matrix log2pow(Matrix &M, int64 P);
Matrix mx_multiply(Matrix &A, Matrix B);
int mod(int64 n);

int main() {
    fin >> K >> X >> N;
    
    Matrix M(K + 1, vector<int>(K + 1));
    Matrix result(K + 1, vector<int>(K + 1));
    result[1][1] = K;
    
    for (int64 i = 1; i <= K; i += 1) {
        M[i][i] = i;
        if (i >= 2) M[i][i - 1] = (K - i + 1);
    }
    
    M = log2pow(M, N - 2);
    mx_multiply(M, result);
    
    fout << result[X][1];
    
    return 0;
}

inline Matrix log2pow(Matrix &M, int64 P) {
    Matrix result = M;
    
    for (int64 p = 1LL; p <= P; p *= 2) {
        if (p & P) mx_multiply(result, M);
        mx_multiply(M, M);
    }
    return result;
}

void mx_multiply(Matrix &A, Matrix &B) {
    int n, m, p;
    n = A.size();
    m = B[0].size();
    p = A[0].size();
    Matrix result(n, vector<int>(p));
    
    for (int i = 1; i < n; i += 1) {
        for (int j = 1; j < m; j += 1) {
            for (int k = 1; k < p; k += 1) {
                result[i][j] = mod(1LL * result[i][j] + 1LL * A[i][k] * B[k][j]);
            }
        }
    }
    
	for (int i = 1; i < n; ++i)
		for (int j = 1; j < m; ++j)
			A[i][j] = result[i][j];
}

inline int mod(int64 n) {
    if (n < MOD) return n;
    if (n < 2 * MOD) return n - MOD;
    return n % MOD;
}
