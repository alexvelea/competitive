//Problem c @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <map>
using namespace std;

const int kMaxN = 1500;

#define int64 long long

map<string, int> getId = {
    {"2", 0},
    {"3", 1},
    {"4", 2},
    {"5", 3},
    {"6", 4},
    {"7", 5},
    {"8", 6},
    {"9", 7},
    {"10", 8},
    {"J", 9},
    {"K", 10},
    {"Q", 11},
    {"A", 12}};

int val[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

long double dp[kMaxN];
int here[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int nrEl, pos;
    while (cin >> nrEl >> pos) {
        int n = nrEl * 11 + 20;
        for (int i = 0; i < n; ++i) {
            here[i] = -1;
            dp[i] = 0.0;
        }
        int last = pos;
        for (int i = 1; i <= nrEl; ++i) {
            string txt; cin >> txt;
            here[pos] = getId[txt];
            last = pos;
            pos += val[getId[txt]];
        }
        pos = last;
        
        for (int i = 1; i <= 10; ++i) {
            dp[i] = 0.1;
        }

        for (int i = 1; i < n; ++i) {
            if (here[i] != -1) {
                dp[i + val[here[i]]] += dp[i];
            } else {
                for (int v = 0; v < 13; ++v) {
                    dp[i + val[v]] += dp[i] / 13.0;
                }
            }
        }

        cout << fixed << setprecision(16) << dp[pos] << '\n';
    }
	return 0;
}
