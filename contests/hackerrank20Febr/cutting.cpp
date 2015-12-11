#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define int64 long long

const int kMaxN = 1000005, Mod = 1000000007;

int A[kMaxN], B[kMaxN];

void mod(int64 &a) {
	if (a >= Mod) 
		a -= Mod;
	if (a >= Mod)
		a %= Mod;
	return ;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		int64 rez = 0;
		cin >> n >> m;
		n--;
		m--;
		for (int i = 0; i < n; ++i)
			cin >> A[i];
		
		for (int i = 0; i < m; ++i)
			cin >> B[i];
		
		sort(A + 0, A + n);
		sort(B + 0, B + m);
		reverse(A + 0, A + n);
		reverse(B + 0, B + m);
		int stA = 0, stB = 0;
		for (; stA < n or stB < m; ) {
			if (stB == m or (A[stA] > B[stB] and stA < n)) {
				rez += 1LL * A[stA] * (stB + 1);
				++stA;
			} else {
				rez += 1LL * B[stB] * (stA + 1);
				++stB;
			}
			mod(rez);
		}
		cout << rez << '\n';
	}
	return 0;
}

