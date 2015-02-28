#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int max_n = 100005;

int dr[max_n], st[max_n];
int w[max_n];

int main() {
	int n, l, r;
	int q1, q2;
	cin >> n >> l >> r;
	cin >> q1 >> q2;
	for (int i = 1; i <= n; ++i)
		cin >> w[i];	
	for (int i = 1; i <= n; ++i)
		st[i] = st[i - 1] + w[i] * l;
	for (int i = n; i; --i)
		dr[i] = dr[i + 1] + w[i] * r;
	int mn = 0x3f3f3f3f;
	for (int i = 0; i <= n; ++i) {
		int s = i;
		int d = n - i;
		int rez = st[i] + dr[i + 1];
 		if (s < d) {
			rez += (d - s - 1) * q2;
		} else 
			if (s > d)
				rez += (s - d - 1) * q1;
 		if (rez < mn)
			mn = rez;
	}
	cout << mn << '\n';
	return 0;	
}
