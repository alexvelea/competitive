#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 405;

string content[kMaxN];
string pattern[kMaxN];

int IsOk[kMaxN][kMaxN];
int n, m, n2, m2;

void Solve(int l1, int l2) {
    int start_l = (l1 - l2 + m + m) % m;
    string p = "#" + pattern[l2];
    string t = "#" + content[l1] + content[l1];
    vector<int> kmpl(m2 + 1, 0);
    int k = 0;
    for (int i = 2; i <= m2; i += 1) {
        while ((k != 0) && (p[k + 1] != p[i]) && p[k + 1] != '?' && p[i] != '?') {
            k = kmpl[k];
        }
        if (p[k + 1] == p[i] || p[k + 1] == '?' || p[i] == '?') {
            k += 1;
        }
        kmpl[i] = k;
    }

    for (auto itr : kmpl) {
        cerr << itr << "\t$\n";
    }

    // kmp on second one
    
    k = 0;
    for (int i = 1; i <= m + m2 - 1 && i <= 2 * m; i += 1) {
        while (k && p[k + 1] != t[i] && p[k + 1] != '?') {
            k = kmpl[k];
        }

        if (p[k + 1] == '?' || p[k + 1] == t[i]) {
            k += 1;
        }

        cerr << i << '\t' << k << '\n';

        if (k == m2) {
            IsOk[start_l][(i - m2) % m] += 1;
            k = kmpl[k];
            cerr << "GO TO \t" << k << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i += 1) {
        cin >> content[i];
    }

    cin >> n2 >> m2;
    for (int i = 0; i < n2; i += 1) {
        cin >> pattern[i];
    }

    Solve(0, 0);
    return 0;

    for (int l = 0; l < n; l += 1) {
        for (int l2 = 0; l2 < n2; l2 += 1) {
            Solve(l, l2);   
        }
    }
 
    if (n2 > n or m2 > m) {
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < m; j += 1) {
                IsOk[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (IsOk[i][j] == n2) {
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << '\n';
    }

    return 0;
}

