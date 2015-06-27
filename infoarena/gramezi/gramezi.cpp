//Problem gramezi @ 17-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

ifstream fin("gramezi.in");
ofstream fout("gramezi.out");

typedef tuple<int, int, int> evState;

int main() {
    int n; fin >> n;
    vector<evState> ev[2];
    for (int i = 1; i <= n; ++i) {
        int a, b; fin >> a >> b;
        ev[0].push_back(make_tuple(a + b, a, i - 1));
        ev[1].push_back(make_tuple(a + b, b, i - 1));
    }
	
    for (int i = 0; i < 2; ++i) {
        sort(ev[i].begin(), ev[i].end());
    }

    vector<int> rez(2);
    vector<bool> viz(n, false);

    for (int remaining = n; remaining;) {
        for (int i = 0; i < 2 and remaining; ++i, --remaining) {
            int v, bonus, ind; 
            tie(v, bonus, ind) = ev[i].back();
            while (viz[ind] == true) {

                ev[i].pop_back();
                tie(v, bonus, ind) = ev[i].back();
            }

            viz[ind] = true;
            rez[i] += bonus;
        }
    }
    fout << rez[0] << ' ' << rez[1] << '\n';
    return 0;
}
