//Problem d @ 21-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long
vector<int> availableHere[17];
 
int64 dp[(1 << 16) + 100][3][2];

int main() {
	ios::sync_with_stdio(false);
    for (int i = 0; i < 16; ++i) {
        int x; cin >> x;
        while (x--) {
            int p; cin >> p;
            availableHere[i].push_back(p);
        }
    }

    dp[0][2][0] = 1;

    for (int s = 0; s < (1 << 16); ++s) {
        int pos = 0;
        for (int i = 0; i < 16; ++i) {
            if (s & (1 << i)) {
                ++pos;
            }
        }

        int lin = (pos / 4) % 2;
/*
        for (int l = 0; l < 3; ++l) {
            for (int c = 0; c < 2; ++c) {
                if (dp[s][l][c] != 0) {
                    cerr << pos << '\t' << s << '\t' << l << '\t' << c << '\n';       
                }
            }
        }
*/
        for (auto itr : availableHere[pos]) {
            if (s & (1 << itr)) {
               ;  
            } else {
                if (itr == 0) {
                    dp[1 | s][lin][0] += dp[s][2][0];
                    dp[1 | s][lin][1] += dp[s][2][1];
                } else {
                    int inversions = 0;
                    for (int j = 1; j < itr; ++j) {
                        if ((s & (1 << j)) == 0) {
                            inversions ^= 1;
                        }
                    }
                    for (int lin = 0; lin < 3; ++lin) {
                        dp[(1 << itr) | s][lin][0 ^ inversions] += dp[s][lin][0];
                        dp[(1 << itr) | s][lin][1 ^ inversions] += dp[s][lin][1];
                    }
                }
            }
        }

    }

    int64 rez = 0;
    rez += dp[(1 << 16) - 1][0][1];
    rez += dp[(1 << 16) - 1][1][0];

    cout << rez << '\n';
	return 0;
}
