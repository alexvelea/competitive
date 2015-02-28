#include <iostream>
using namespace std;
string t;
int main() {
	cin >> t;
	int nr = 0, nr_m = 0;
	int mx = 0;
	int st = 0;
	while (t[st] == 'F')
		++st;
	for (; st < int(t.size()); ++st) {
		if (t[st] == 'M' && t[st - 1] == 'M')
			--nr;
		if (t[st] == 'F' && t[st - 1] == 'F')
			++nr;
		if (nr < 0)
			nr = 0;
		if (t[st] == 'M')
			++nr_m;
		if (t[st] == 'F' && nr_m + nr > mx)
			mx = nr_m + nr;
	}
	cout << mx << '\n';
	return 0;
}
