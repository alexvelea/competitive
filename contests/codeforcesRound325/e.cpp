//Problem e @ 12-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int kMaxN = 1e5 + 5, kMaxVal = 1e7 + 7, kMod = 1e9 + 7;

#define int64 long long

int Div[kMaxVal], here[kMaxVal];
vector<int> primes;

int rez = 0;

void bt(int el, int ind, int here) {
    rez += (1 << here);
    
    for (int i = ind; i < int(primes.size()) and 1LL * el * primes[ind] < kMaxVal; ++i) {
        bt(el * primes[ind], i + 1, here + 1);
    }
}

int main() {
	ios::sync_with_stdio(false);
	time_t t = clock();
    for (int d = 2; d * d <= kMaxVal; ++d) {
        if (Div[d] == 0) {
            for (int j = d * d; j <= kMaxVal; j += d) {
                if (Div[j] == 0) {
                    Div[j] = d;
                }
            }
        }
    }
    
/*
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        here[x]++;
    }
*/

    for (int i = 2; i <= kMaxVal; ++i) {
        if (Div[i] == 0) {
            primes.push_back(i);
            Div[i] = i;
        }
    }
    bt (1, 0, 0);
    cerr << rez << '\n';
    cerr << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n'; 
    return 0;
}
