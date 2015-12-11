#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int inf = 0x3f3f3f3f;

bool edge[105][105];

void add(int a, int b) {
	edge[a][b] = edge[b][a] = true;
}

int main() {
	int k;
	const int base = 67;
	cin >> k;
	               
	add(1, 3);
	add(1, 4);
	if (k & 1)
		add(base, 3);
	for (int i = 1; i < 32; ++i) {
		int a = i * 2 + 3;
		add(a - 1, a);
		add(a - 2, a);
		add(a - 1, a + 1);
		add(a - 2, a + 1);

		if (k & (1 << i)) {
			add(base + i, a);
		}
	}
	for (int i = 0; i < 31; ++i)
		add(base + i, base + i + 1);
	add(base + 31, 2);
	cout << "100\n";
	for (int i = 1; i <= 100; ++i, cout << '\n')
		for (int j = 1; j <= 100; ++j)
			cout << (edge[i][j] == true ? "Y" : "N");
	return 0;
}
