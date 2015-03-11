#include <iostream>
using namespace std;

int n, k, rez;

void back(int nrEl, int last, int sum) {
	if (nrEl == k + 1) {
		if (sum == n) {
			++rez;
		}
		return ;
	}

	for (int i = last + 1; i  + sum <= n; ++i) {
		back(nrEl + 1, i, sum + i);
	}
}

int main() {
	cin >> n >> k;
	back(1, 0, 0);
	cout << rez << '\n';
	return 0;
}
