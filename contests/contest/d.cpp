//Problem d @ 08-08-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
    double aux;
    while (cin >> aux) {
        int required = int(aux * 100 + 0.1);
        vector<int> nrEl(4), rez(4);
        for (int i = 0; i < 4; ++i) {
            cin >> nrEl[i];
        }

        int mx = inf;

        for (int a = 0; a <= nrEl[0]; ++a) {
            for (int b = 0; b <= nrEl[1]; ++b) {
                for (int c = 0; c <= nrEl[2]; ++c) {
                    int needed = required - a * 25 - b * 10 - c * 5;
                    if (needed >= 0 and needed <= nrEl[3]) {
                        if (a + b + c + needed < mx) {
                            mx = a + b + c + needed;
                            rez[0] = a;
                            rez[1] = b;
                            rez[2] = c;
                            rez[3] = needed;
                        }
                    }
                }
            }
        }
        if (mx == inf) {
            cout << "NO EXACT CHANGE\n";
        } else {
            cout << rez[0] << ' ' << rez[1] << ' ' << rez[2] << ' ' << rez[3] << '\n';
        }
    }
	return 0;
}
