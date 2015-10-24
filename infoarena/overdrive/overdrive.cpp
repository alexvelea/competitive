//Problem overdrive @ 16-07-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 32, inf = 0x3f3f3f3f;

#define int64 long long

ifstream fin("overdrive.in");
ofstream fout("overdrive.out");

int el[kMaxN];

int main() {
    int n; fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> el[i];
    }

    if (n == 1) {
        fout << el[0] << '\n';
        return 0;
    }

    int a = n / 2;
    int b = n - a;
    vector<pair<int64, bool> > event;
    for (int i = 0; i < (1 << a); ++i) {
        int64 now = 0;
        for (int j = 0; j < a; ++j) {
            if (i & (1 << j)) {
                now -= el[j];
            } else {
                now += el[j];
            }
        }
        event.push_back(make_pair(now, false));
    }

    for (int i = 0; i < (1 << b); ++i) {
        int64 now = 0;
        for (int j = 0; j < b; ++j) {
            if (i & (1 << j)) {
                now -= el[j + a];
            } else {
                now += el[j + a];
            }
        }
        event.push_back(make_pair(now, true));
    }

    sort(event.begin(), event.end());

    int64 last[2] = {-1LL * inf * inf, -1LL * inf * inf}, mn = 1LL * inf * inf;
    for (auto itr : event) {
        last[itr.second] = itr.first;
        mn = min(mn, abs(last[0] - last[1]));
    }

    int64 sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += el[i];
    }

    sum += mn;
    fout << sum / 2 << '\n';

	return 0;
}
