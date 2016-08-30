#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n = 300;
    int cnt = 1;
    int target = 300 * 3;
    int remaining = 0;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (i == n - 1 and j == n - 1) {
                matrix[i][j] = ++cnt;
            } else {
                if (remaining == 0) {
                    remaining = target;
                    cnt += 1;
                }
                remaining -= 1;
                matrix[i][j] = cnt;
            }
        }
    }
    cout << n << ' ' << n << ' ' << cnt << '\n';
    for (auto a : matrix) {
        for (auto b : a) {
            cout << b << ' ';
        }
        cout << '\n';
    }
}
