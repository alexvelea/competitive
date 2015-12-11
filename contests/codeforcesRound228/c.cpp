#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int inf = 0x3f3f3f3f;

int best[105][105], el[105];

vector<int> rez;

int main() {
	int n, a = 0, b = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int s;
		cin >> s;
		for (int j = 1; j <= s; ++j)
 			cin >> el[j];
		for (int j = 1; j <= s/2; ++j)
			a += el[j];
		for (int j = s; j > s - int(s / 2); --j)
			b += el[j];
		if (s % 2 == 1)
			rez.push_back(el[(s + 1) / 2]);
	}
	sort(rez.begin(), rez.end());
	reverse(rez.begin(), rez.end());
	for (int i = 0; i < int(rez.size()); ++i) {
		if (i % 2 == 0)
			a += rez[i];
		else
			b += rez[i];
	}
	cout << a << ' ' << b << '\n';
	return 0;
}
