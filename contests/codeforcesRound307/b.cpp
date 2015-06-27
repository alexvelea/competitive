//Problem b @ 16-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int apA[26], apB[26], apC[26];

int main() {
	ios::sync_with_stdio(false);
    string a, b, c; cin >> a >> b >> c;
    
    for (auto itr : a) {
        apA[itr - 'a']++;
    }
    
    for (auto itr : b) {
        apB[itr - 'a']++;
    }
    
    for (auto itr : c) {
        apC[itr - 'a']++;
    }

    int mx = 0, rB = 0, rC = 0;
    for (int nrB = 0; nrB < int(a.size()); ++nrB) {
        // test if it's possible
        int nrC = inf;
        bool ok = true;
        for (int i = 0; i < 26; ++i) {
            int x = apA[i] - nrB * apB[i];
            if (x < 0) {
                ok = false;
            }
            if (apC[i]) {
                nrC = min(nrC, x / apC[i]);
            }
        }
        if (not ok) {
            break;
        }
        if (nrB + nrC > mx) {
            mx = nrB + nrC;
            rB = nrB;
            rC = nrC;
        }
    }
    for (int i = 0; i < rB; ++i) {
        cout << b;
    }
    for (int i = 0; i < rC; ++i) {
        cout << c;
    }
    for (int l = 0; l < 26; ++l) {
        apA[l] -= rB * apB[l] + rC * apC[l];
    }
    for (int l = 0; l < 26; ++l) {
        while (apA[l]) {
            cout << char(l + 'a');
            apA[l]--;
        }
    }
	return 0;
}
