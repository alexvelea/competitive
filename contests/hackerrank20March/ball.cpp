#include <iostream>
using namespace std;
int main() {
	int t;
	cin >> t;

	for (int ind = 0; ind < 3; ++ind)
		cin >> L[ind];

	for (int ind = 0; ind < 2; ++ind)
		for (int i = 0; i < 3; ++i)
			cin >> coord[ind][i][0];

	for (int ind = 0; ind < 2; ++ind)
		for (int st = 0; st < 8; ++st)
			for (int i = 0; i < 3; ++i) {
				coord[i][ind][st] = coord[i][ind][0];
				if (st & (1 << i))
					coord[ind][i][st] = 2 * L[i] - coord[ind][i][st];
			}
	
	for (int i = 0; i < 3; ++i)
		cin >> st_coord[i];
	for (int i = 0; i < 2; ++i)
		for (int st = 0; st < 8; ++st)
			for (int i = 0; i < 3; ++i)
				coord[ind][i][st] -= st_coord[i];

 	cin >> n;
	for (int = -n; a <= n; ++a)
	return 0;
}
