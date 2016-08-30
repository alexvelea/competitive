#include <cassert>
#include <cmath>

#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f, kMod = 1e9+7;

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

int Pow(int64 x, int base, int kMod = 1e9+7) {
    int result = 1;
    while (x) {
        if (x % 2 == 1) {
            result = (1LL * result * base) % kMod;
        }
        x /= 2;
        base = (1LL * base * base) % kMod;
    }
    return result;
}

int main() {
    Matrix<> m({{4, 0}, {kMod - 1, 1}});
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    
    double p = 0;

    bool deleted = false;
    int p1=1, p2=1;

    int answer = 1;
    for (int i = 0; i < n; i += 1) {
        int64 x; cin >> x;
        p += log2(x);
        answer *= x;

        if (deleted == false and x % 2 == 0) {
            p1 = (1LL * p1 * (x / 2)) % (kMod - 1);
            deleted = true;
        } else {
            p1 = (1LL * p1 * x) % (kMod - 1);
        }
        
        p2 = (1LL * p2 * x) % (kMod - 1);
    }

    if (p <= 1.1) {
        if (answer == 1) {
            cout << "0/1\n";
        } else if (answer == 2) {
            cout << "1/2\n"; 
        }
    } else {
        int64 B = Pow(p2 + kMod - 2, 2);
        int64 result = 0;
 //       cerr << p1 << '\n';
        if (deleted) {
            result = (Matrix<>({{1, 1}}) * (Matrix<>({ {4, 0}, {kMod - 1, +1}})).pow(p1)).element[0][0];
        } else {
        //    cout << ((1LL * (p1 + 1) * Pow(500000001, 2, (int)1e9+6))%(int)(1e9+6)) << "#@!#!@\n";
            const int p6 = 1e9+6;
            result = (Matrix<>({{1, 1}}) * (Matrix<>({ {4, 0}, {kMod - 1, +1}}).pow((1LL * (p1 - 1) * Pow(500000001, 2, (int)p6))%(int)(p6)))).element[0][0];
        }
      //  cout << result << "RESULT\t";
        if (deleted) {
            result += 1;
            result %= kMod;
            result = (1LL * result * Pow(1LL * kMod - 2, 4)) % kMod;
        } else {
            result += kMod - 1;
            result %= kMod;
            result = (1LL * result * Pow(1LL * kMod - 2, 2)) % kMod;
        } 
        cout << result << "/" << B << '\n';
    }
           


    return 0;
}
