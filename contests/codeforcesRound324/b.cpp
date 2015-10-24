//Problem b @ 06-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int kMod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    int64 a = 27, A = 1;
    int64 b = 7, B = 1;
	for (int i = 1; i <= n; ++i) {
        A = A * a % kMod;
        B = B * b % kMod;
    }
    A -= B;
    A += kMod;
    cout << A % kMod;
    return 0;
}
