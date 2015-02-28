#include <ctime>
#include <cstdlib>

#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 125000 * 200;

struct abc {
	int x, y, z;
	abc() {
		x = y = z = 0;
	}
	abc(int _a, int _b, int _c) {
		x = _a;
		y = _b;
		z = _c;
	}
	bool operator < (const abc &rhs) const {
		if (x == rhs.x) {
			if (y == rhs.y) 
				return z < rhs.z;
			return y < rhs.y;
		}
		return x < rhs.x;
	}
};


vector<abc> el2;
vector<pair<pair<int, int>, int> > el;

int main() {
	time_t t = clock();
	srand(time(NULL));
	int n = kMaxN;
	for (int i = 1; i < n; ++i) {
		el.push_back(make_pair(make_pair(rand(), rand()), rand()));
//		el2.push_back(abc(rand(), rand(), rand()));
	}
	sort(el.begin(), el.end());
//	sort(el2.begin(), el2.end());

	cerr << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n';
	return 0;
}
