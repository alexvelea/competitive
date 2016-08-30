#include <algorithm>
#include <functional>

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

template<int kMod=(int)1e9+7>
struct Matrix {
  public:
    int n, m;
    vector<vector<int>> element;
  public:
    Matrix(int n, int m) : n(n), m(m), element(n, vector<int>(m, 0)) { }

    Matrix(int n) : n(n), m(n), element(n, vector<int>(n, 0)) { 
        for (int i = 0; i < n; i += 1) {
            element[i][i] = 1;
        }
    }

    Matrix(const vector<vector<int>>& element) 
        : n((int)element.size()), m((int)element[0].size()), element(element) {
        for (auto& line : element) {
            assert((int)line.size() == m);
        }
    }

    Matrix& operator*=(const Matrix& rhs) {
        assert(n == m and rhs.n == rhs.m);
        vector<vector<int>> result(n, vector<int>(n));
        for (int l = 0; l < n; l += 1) {
            for (int c = 0; c < n; c += 1) {
                for (int itr = 0; itr < n; itr += 1) {
                    result[l][c] = (result[l][c] + 1LL * element[l][itr] * rhs.element[itr][c]) % kMod;       
                }
            }
        }

        element = move(result);
        return *this;
    }

    Matrix operator*(const Matrix& rhs) const {
        assert(m == rhs.n);
        Matrix result(n, rhs.m);
        for (int l = 0; l < n; l += 1) {
            for (int c = 0; c < rhs.m; c += 1) {
                for (int itr = 0; itr < m; itr += 1) {
                    result.element[l][c] = (result.element[l][c] + 1LL * element[l][itr] * rhs.element[itr][c]) % kMod;       
                }
            }
        }       

        return result;
    }

    Matrix pow(int64 p) const {
        assert(n == m);

        Matrix result(n);
        Matrix base(*this);
        while (p) {
            if (p & 1) {
                result = result * base;
            }
            base *= base;
            p /= 2;
        }
        return result;    
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int64 k; cin >> k;
    vector<int64> element(n);
    for (int i = 0; i < n; i += 1) {
        cin >> element[i];
    }
    
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            int64 p = element[i] ^ element[j];
            int num = 0;
            while (p) {
                num += 1;
                p -= p & (-p);
            }

            if (num % 3 == 0) {
                matrix[i][j] = true;
            }
        }
    }

    Matrix<> m(matrix);
    Matrix<> result(vector<vector<int>>(1, vector<int>(n, 1)));
    cout << (result * m.pow(k - 1) * Matrix<>(vector<vector<int>>(n, vector<int>(1, 1)))).element[0][0];
    
    return 0;
}
