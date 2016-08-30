#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("minmaxstore.in");
ofstream fout("minmaxstore.out");

const int kMaxN = 1e5+5;
pair<bool, bool> ok[kMaxN];

int main() {
    int t; fin >> t;
    while (t--) {
        int n, m; fin >> n >> m;
        for (int i = 0; i < n; i += 1) {
            ok[i] = {true, true};
        }

        for (int i = 0; i < m; i += 1) {
            int a, b; fin >> a >> b;
            if (a == b) {
                continue;
            }

            a--;
            b--;
            ok[a].first = ok[a].first | ok[b].first;
            ok[b].second = ok[a].second | ok[b].second;

            ok[a].second = false;
            ok[b].first = false;
        }

        pair<int, int> num;
        int minP, maxP;
        for (int i = 0; i < n; i += 1) {
            if (ok[i].first) {
                minP = i;
            }
            if (ok[i].second) {
                maxP = i;
            }
            num.first += ok[i].first;
            num.second += ok[i].second;
        }

        int minC, maxC; fin >> minC >> maxC;
        minC--;
        maxC--;

        if ((num.first == 1 and minP == minC) and (num.second == 1 and maxP == maxC)) {
            fout << "Popeala";
        } else if ((num.first == 1 and minP == minC) and not (num.second == 1 and maxP == maxC)) {
            fout << "Popel";
        } else if (not (num.first == 1 and minP == minC) and (num.second == 1 and maxP == maxC)) {
            fout << "Popita";
        } else {
            fout << "Comisarul";
        }

        fout << '\n';
    }
    return 0;
}
