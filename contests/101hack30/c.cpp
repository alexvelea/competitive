//Problem c @ 21-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 1e5 + 5;

#define int64 long long

int n, k;
int a[kMaxN], b[kMaxN], rez[kMaxN];

int64 max(int a, int64 b) {
    if (a > b) {
        return a;
    } return b;
}

int min(int a, int64 b) {
    if (a < b) {
        return a;
    } return b;
}

int64 check(int64 time) {
    int64 rez = 0;
    for (int i = 1; i <= n; ++i) {
        rez += max(0, min(1LL * a[i], time / b[i])); 
    }
    return rez;
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> k;
    int64 total = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        total += a[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    if (k >= total) {
        for (int i = 1; i <= n; ++i) {
            cout << 0 << ' ';    
        }
        return 0;
    }

    int64 rezTime = -1, expected = total - k;
    expected = max(0, expected);

    for (int p = 60; p >= 0; --p) {
        if (check((1LL << p) + rezTime) < expected) {
            rezTime += (1LL << p);    
        }
    }
    int64 now = check(rezTime);
	for (int i = 1; i <= n; ++i) {
        rez[i] = min(a[i], rezTime / b[i]);
    }
    rezTime += 1;
    for (int i = n; i; --i) {
        if (now < expected) {
            if (1LL * a[i] * b[i] >= rezTime and rezTime %b[i] == 0) {
                rez[i]++;
                now++;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << rez[i] << ' ';
    }
    return 0;
}
