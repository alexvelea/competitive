#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, mod = 1e9+7;
typedef long double Double;

const Double log[] = {0, 0, 1, 1.5849625007211561814};

void GetBest(pair<Double, int>& a, pair<Double, int>& b) {
    if (b.first > a.first) {
        a = b;
    }
}

pair<Double, int> Solve(vector<vector<int>> matrix, vector<vector<bool>> ok) {
    int n = int(matrix.size());
    vector<vector<int>> maxD(n, vector<int>(n, +inf));
    for (int i = 0; i < n; i += 1) {
        int current = 0;
        for (int j = 0; j < n; j += 1) {
            if (matrix[i][j] == 0) {
                current = 0;
            } else {
                current += 1;
            }
            maxD[i][j] = min(maxD[i][j], current);
        }
    }

    for (int i = 0; i < n; i += 1) {
        int current = 0;
        for (int j = n - 1; j >= 0; j -= 1) {
            if (matrix[i][j] == 0) {
                current = 0;
            } else {
                current += 1;
            }
            maxD[i][j] = min(maxD[i][j], current);
        }
    }

    for (int j = 0; j < n; j += 1) {
        int current = 0;
        for (int i = 0; i < n; i += 1) {
            if (matrix[i][j] == 0) {
                current = 0;
            } else {
                current += 1;
            }
            maxD[i][j] = min(maxD[i][j], current);
        }
    }

    for (int j = 0; j < n; j += 1) {
        int current = 0;
        for (int i = n - 1; i >= 0; i -= 1) {
            if (matrix[i][j] == 0) {
                current = 0;
            } else {
                current += 1;
            }
            maxD[i][j] = min(maxD[i][j], current);
        }
    } 
/*
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            cerr << maxD[i][j];
        }
        cerr << '\n';
    }
    cerr << "\n\n";
*/    

    vector<vector<Double>> Sum(n, vector<Double>(n, 0.0));
    auto PartialSum = [&](int i, int j) -> Double {
        if (i == -1 or j == -1) {
            return 0.0;
        }
        return Sum[i][j];
    };


    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            Sum[i][j] = log[matrix[i][j]] + PartialSum(i - 1, j) + PartialSum(i, j - 1) - PartialSum(i - 1, j - 1);
        }
    }

    pair<int, int> where = {0, 0};
    Double best_cost = 0.0;

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (maxD[i][j] == 0 or not ok[i][j]) {
                continue;
            }
            int d = maxD[i][j] - 1;
            Double current = 0;
            current += PartialSum(i, j + d);
            current -= PartialSum(i - 1, j + d);
            current -= PartialSum(i, j - d - 1);
            current += PartialSum(i - 1, j - d - 1);

            current += PartialSum(i + d, j);
            current -= PartialSum(i + d, j - 1);
            current -= PartialSum(i - d - 1, j);
            current += PartialSum(i - d - 1, j - 1);

            current -= log[matrix[i][j]];
//            cerr << i << '\t' << j << '\t' << current << '\n';

            if (current > best_cost) {
                best_cost = current;
//                cerr << best_cost << '\n';
                where = {i, j};
            }
        }
    }

    int x = where.first;
    int y = where.second;
    int d = maxD[x][y] - 1;
    int int_cost = matrix[x][y];

//    cerr << x << '\t' << y << '\t' << best_cost << '\n';

    for (int i = 1; i <= d; i += 1) {
        int_cost = (1LL * int_cost * matrix[x - i][y] * matrix[x + i][y] * matrix[x][y - i] * matrix[x][y + i]) % mod;
    }
    return {best_cost, int_cost};
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            char c; cin >> c;
            matrix[i][j] = c - '0';
        }
    }

    vector<vector<bool>> ok(2 * n + 1, vector<bool>(2 * n + 1, false));
    vector<vector<int>> matrix2(2 * n + 1, vector<int>(2 * n + 1, 1));

    for (int len = -1; len <= n + n; len += 1) {
        for (int i = -1; i <= len + 1; i += 1) {
            int j = len - i;

            if (len >= 0 and len < 2 * n + 1 and (n - len + 2 * j) >= 0 and (n - len + 2 * j) < 2 * n + 1) {
//                cerr << len << '\t' << n - len + 2 * j << '\n';
                matrix2[len][n - len + 2 * j] = 0; 
            }

            if (i >= n or j >= n or i < 0 or j < 0) {
                continue;
            }
//            cerr << i << '\t' << j << '\n';
            ok[len][n - len + 2 * j] = true;
            matrix2[len][n - len + 2 * j] = matrix[i][j];
        }
//        cerr << '\n';
    }
/*    
    for (auto itr : matrix2) {
        for (auto el : itr) {
            cout << el << ' ';
        }
        cout << '\n';
    }

    for (auto itr : ok) {
        for (auto el : itr) {
            cout << el << ' ';
        }
        cout << '\n';
    }
*/
    auto a = Solve(matrix, vector<vector<bool>>(n, vector<bool>(n, true)));
    auto b = Solve(matrix2, ok);
    GetBest(a, b);
    cout << a.second << '\n';
    return 0;
}
