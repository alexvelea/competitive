#include <iostream>
using namespace std;

int n, rez, nr[40], INF = 100000;

void bt (int x) {
	if (x == n + 1) {
		rez ++;
		if (rez >= 1000000)
			rez -= 1000000;
		return ;
	}
	int i = 0;
	if (x > 2)
		i = max (i, nr[x-2]);
	if (x > 3)
		i = max (i, nr[x-3]);
	
	for (++i; i <= n; ++i) {
		nr[x] = i;
		bt (x+1);
	}
}

int main() {
	cin >> n;
	bt (1);
	cout << rez << "\n";
}
