#include <iostream>
using namespace std;

const int n = 2;

double comb[n + 1][n + 1];
double fact[n + 1], rez[n + 1];
bool taken[n + 1][n + 1];

void computeDp(int n) {
    for (int i = 1; i <= n; ++i) {
        taken[n][i] = true;
    }
    rez[n] = 1.0 * (n + 1) / 2;

    for (int i = n - 1; i; --i) {
        for (int pos = 1; pos <= i; ++pos) {
            double chx = 0, pondered = 0;
            for (int inFront = 0; inFront <= n - i; ++inFront) {
                pondered += 1.0 * (inFront + pos) * comb[pos - 1 + inFront][inFront] * comb[n - pos - inFront][n - i - inFront]; 
                chx += 1.0 * comb[pos - 1 + inFront][inFront] * comb[n - pos - inFront][n - i - inFront];
            }
            pondered /= chx;
            if (rez[i + 1] < pondered) {
                taken[i][pos] = false;
                rez[i] += rez[i + 1];
            } else {
                taken[i][pos] = true;
                rez[i] += pondered;
            }
        }
        rez[i] /= i;
    }
    

    for (int i = 1; i <= n; ++i) {
        cerr << i << '\t' << rez[i] << '\n';
    }

    for (int i = 1; i <= n; ++i) {
        cerr << i << '\t';
        for (int j = 1; j <= i; ++j) {
            cerr << taken[i][j];
        }
        cerr << '\n';
    }
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1.0 * fact[i - 1];
    }

    for (int i = 0; i <= n; ++i) {
        comb[i][0] = 1.0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
    computeDp(n);

    return 0;
}
