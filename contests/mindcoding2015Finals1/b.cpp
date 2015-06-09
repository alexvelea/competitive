//Problem b from mindcoding2015Finals1
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
 	double radius; cin >> radius;
	cout << "0.0 0.0\n";
	cout.flush();

	while (1) {
		double x, y;
		cin >> x >> y;
		cout << -x << ' ' << -y << '\n';
		cout.flush();
	}
	return 0;
}
