#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
int n, m; 

int el[30][30];

bool check() {
    for (int i = 0; i < n; i += 1) {
        int num = 0;
        for (int j = 0; j < m; j += 1) {
            if (el[i][j] - 1 != j) {
                num += 1;
            }
        }
        if (num > 2) {
            return false;
        }
    }
    return true;
}

void Swap(int i, int j) {
    for (int l = 0; l < n; l += 1) {
        swap(el[l][i], el[l][j]);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> el[i][j];
        }
    }

    if (check()) {
        cout << "YES\n";
        return 0;
    }

    for (int i = 0; i < m; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (i == j) {
                continue;
            }

            Swap(i, j);
            if (check()) {
                cout << "YES\n";
                return 0;
            }
            Swap(i, j);
        }
    }
    cout << "NO\n";

    return 0;
}
