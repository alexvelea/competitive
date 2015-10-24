//Problem c @ 06-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    int n, t; cin >> n >> t;
    string a, b; cin >> a >> b;
    int difab = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            difab++;
        }
    }
    string c = a;
    if (difab > 2 * t) {
        cout << "-1\n";
        return 0;
    }
    int A = difab / 2;
    int B = difab / 2;
    int all = t - difab;
    int allDif = difab % 2;

    if (difab <= t) {
        allDif = difab;
        all = t - difab;
        A = B = 0;
    } else {
        all = 0;
        allDif = 2 * t - difab;
        A = B = (difab - allDif) / 2;
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            if (A) {
                --A;
                c[i] = b[i];
            } else if (B) {
                --B;
                c[i] = a[i];
            } else if (allDif) {
                for (char C = 'a'; ; ++C) {
                    if (a[i] != C and b[i] != C) {
                        c[i] = C;
                        --allDif;
                        break;
                    }
                }
            }
        } else {
            c[i] = a[i];
            if (all) {
                if (a[i] == 'a') {
                    c[i] = 'b';
                } else {
                    c[i] = 'a';
                }
                --all;
            }
        }
    }
    if (A || B || all) {
        cout << "-1\n";
    } else {
        cout << c << '\n';
    }
	return 0;
}
