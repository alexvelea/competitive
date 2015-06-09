#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
	int a, b, c, d; cin >> a >> b >> c >> d;
	if (1.0 * a * d - 1.0 * b* c == 0.0) {
		cout << fixed << setprecision(11) << 0.0 << '\n';
		return 0;
	}

	double mn = 1.0 * inf * inf;
 	for (int i = 0; i < 3 * 3 * 3 * 3; ++i) {
		double rez = 1.0 * inf * inf;
		vector<int> v = {a, b, c, d};	
		vector<int> vp = {0, 0, 0, 0};
		vector<int> bonus = {1, 1};
		int p = i;
		for (int j = 0; j < 4; ++j) {
			vp[j] = ((p % 3) - 1);
        	p /= 3;
		}

		double a = 0, b = 0, c = 0;
		a += 1.0 * vp[0] * vp[3];
		c += 1.0 * v[0] * v[3];
		b += 1.0 * v[0] * vp[3];
		b += 1.0 * v[3] * vp[0];

		a -= 1.0 * vp[1] * vp[2];
		c -= 1.0 * v[1] * v[2];
		b -= 1.0 * v[1] * vp[2];
		b -= 1.0 * v[2] * vp[1];

		if (a == 0.0) {
			rez = fabs(c / b);
		} else {
			double delta = b * b - 4 * a * c;
			if (delta < 0) 
				rez = 1.0 * inf * inf; 
			else {
				double sq = sqrt(delta);
				double x1 = fabs((-b + sq) / 2.0 / a);
				double x2 = fabs((-b - sq) / 2.0 / a);
				rez = min(x1, x2);
			}
		}
		mn = min(mn, rez);
	}
	
	cout << fixed << setprecision(11) << mn << '\n';

	return 0;
}
