#include <iostream>
using namespace std;
int main() {
	in >> a >> b;
	int n, m;
	int n = a.size();
	int m = b.size();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (a[i - 1] != b[j - 1]) {
				mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]);
			} else {
				mx[i][j] = mx[i - 1][j - 1] + 1;
			}
	return 0;
}
