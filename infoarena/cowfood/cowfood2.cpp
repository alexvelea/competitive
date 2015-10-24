#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxK = 31, kMaxN = 21, kMaxS = 1e4 + 4, kMod = 3210121;

int el[kMaxN][kMaxK];
int comb[kMaxK][kMaxS + kMaxK];

void mod(int &a) {
    if (a >= kMod) {
        a -= kMod;
    } else if (a < 0) {
        a += kMod;
    }
}

ifstream fin("cowfood.in");
ofstream fout("cowfood.out");

int main() {
    int k, sum, n; fin >> k >> sum >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            fin >> el[i][j];
        }
    }

    comb[0][0] = 1;
    for (int i = 1; i < kMaxS + kMaxN; ++i) {
        comb[0][i] = 1;
        for (int j = 1; j < kMaxK; ++j) {
            comb[j][i] = comb[j][i - 1] + comb[j - 1][i - 1];
            mod(comb[j][i]);
        }
    }

    int rez = 0;

    for (int s = 1; s < (1 << n); ++s) {
        vector<int> mx(k, 0);
        bool sign = false;
        for (int i = 0; i < n; ++i) {
            if (s & (1 << i)) {
                for (int j = 0; j < k; ++j) {
                    mx[j] = max(mx[j], el[i][j]);
                }
                sign ^= 1;
            }
        }

        int remaining = sum;
        for (auto itr : mx) {
            remaining -= itr;
        }

        if (remaining < 0) {
            continue;
        }
        int thing = comb[k][k + remaining];
        if (sign) {
            rez += thing;
        } else {
            rez -= thing;
        }
        mod(rez);
    }
    int f = (comb[k][k + sum] - rez - (1LL * k * sum) % kMod + 2 * kMod - 1) % kMod;
    fout << f << '\n';
    return 0;
}

