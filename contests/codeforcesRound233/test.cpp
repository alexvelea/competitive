#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int n, target[100], el[100];

int targetB[100], col[100];

int bt() {
	int x = rand() % n;
	int y = rand() % n;
	el[x] = true;
	col[y] = true;
	int ok = true;
	for (int i = 0; i < n; ++i)
		if (target[i] and not el[i])
			ok = false;
	for (int i = 0; i < n; ++i)
		if (targetB[i] and not col[i])
			ok = false;
	if (ok)
		return 1;
	return bt() + 1;
}

int main() {
	srand(time(NULL));
	int t = 10000000;
	n = 5;
	target[0] = true;
	target[1] = true;
	target[2] = true;
	targetB[0] = targetB[1] = targetB[2] = true;
	int rez = 0;
	for (int i = 1; i <= t; ++i) {
		rez += bt();
		for (int j = 0; j < n; ++j)
			el[j] = 0;
		for (int j = 0; j < n; ++j)
			col[j] = 0;
	}

	cout << 1.0 * rez / t;
}
