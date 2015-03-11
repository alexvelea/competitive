//Problem compunere from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 4005;

ifstream in("compunere.in");
ofstream out("compunere.out");

int dp[kMaxN][kMaxN];
int a[kMaxN], b[kMaxN];

int main() {
    int n, m; in >> n >> m;
    if (n > kMaxN or m > kMaxN) {
        out << "Nasol, boß\n";
    } else {
        for (int i = 1; i <= n; ++i) {
            in >> a[i];
        }
        for (int j = 1; j <= m; ++j) {
            in >> b[j];
        }
        
        for (int i = n; i; --i) {
            for (int j = m; j; --j) {
                if (a[i] == b[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }
        
        vector<int> rez;
        
        int A = 1, B = 1;
        for (; A <= n and B <= m;) {
            if (a[A] == b[B]) {
                rez.push_back(a[A]);
                ++A; ++B;
            } else {
                if (dp[A + 1][B] == dp[A][B + 1]) {
                    if (a[A] < b[B]) {
                        rez.push_back(a[A]);
                        ++A;
                    } else {
                        rez.push_back(b[B]);
                        ++B;
                    }
                } else {
                    if (dp[A + 1][B] > dp[A][B + 1]) {
                        rez.push_back(a[A]);
                        ++A;
                    } else {
                        rez.push_back(b[B]);
                        ++B;
                    }
                }
            }
        }
        
        while (A <= n) {
            rez.push_back(a[A]);
            ++A;
        }
        
        while (B <= m) {
            rez.push_back(b[B]);
            ++B;
        }
        
        out << rez.size() << '\n';
        for (auto itr : rez) {
            out << itr << ' ';
        }
    }
	in.close();
	out.close();
    return 0;
}
