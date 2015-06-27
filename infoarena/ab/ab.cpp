//Problem ab @ 16-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 30005;
const double eps = 1e-7;

#define int64 long long

ifstream fin("ab.in");
ofstream fout("ab.out");

int compute(vector<int> a, vector<int> &cost) {
    if (a.size() > cost.size()) {
        return inf;
    }

    for (int i = 0; i < int(a.size()); ++i) {
        for (int j = i + 1; j < int(a.size()); ++j) {
            if (a[i] < a[j]) {
                swap(a[i], a[j]);
            }
        }
    }

    int rez = 0;
    for (int i = 0; i < int(a.size()); ++i) {
        rez += cost[i] * a[i];
    }
    return rez;
}

int b[kMaxN];

int main() {
    int t; fin >> t;
    while (t--) {
        int n, m, k; fin >> n >> m >> k;
        vector<int> cost;
        for (int i = 1; i <= k; ++i) {
            int x; fin >> x;
            cost.push_back(x);
        }
        sort(cost.begin(), cost.end());
        
        for (int i = 1; i <= n; ++i) {
            fin >> b[i];
            b[i] += b[i - 1];
        }

        int rez = inf;
    
        for (int i = 1; i <= n; ++i) {
            rez = min(rez, compute(vector<int> {i + (m - b[i]), b[i], n - i}, cost));
        }
        rez = min(rez, compute(vector<int> {n, m}, cost));

        fout << rez << '\n';
    }
	return 0;
}
