//Problem a @ 06-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 4005;

#define int64 long long

int n;
bool inLine[kMaxN];
int64 v[kMaxN], p[kMaxN], d[kMaxN];

void cry(int ind, int64 val) {
    inLine[ind] = false;
    for (int i = ind; i <= n and val; ++i) {
        if (inLine[i] == true) {
            p[i] -= val;
            --val;
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> d[i] >> p[i];
        inLine[i] = true;
    }
    vector<int> rez;
    for (int i = 1; i <= n; ++i) {
        if (inLine[i]) {
            rez.push_back(i);
            cry(i, v[i]);
            for (int j = i; j <= n; ++j) {
                if (inLine[j] == true and p[j] < 0) {
                    inLine[j] = false;
                    for (int k = j; k <= n; ++k) {
                        p[k] -= d[j];
                    }
                    j = i - 1;
                }
            }
        }
    }
    cout << rez.size() << '\n';
    for (auto itr : rez) {
        cout << itr << ' ';
    }
	return 0;
}
