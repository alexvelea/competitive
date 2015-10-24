//Problem 1 @ 04-10-2015
#include <iostream>
#include <cmath>
using namespace std;

#define int64 long long

long double a, b, c;

int main() {
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);

    int n;
    cin >> n;
    while (n--) {
        cin >> a >> b >> c;
        int eps = 100000;
        int A, B, C;
        A = round(a * eps);
        B = round(b * eps);
        C = round(c * eps);
        if (1LL * A * B * C > 1LL * eps * A * B + 1LL * eps * B * C + 1LL * eps * A * C) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
	return 0;
}
