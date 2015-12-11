#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream in("ninja.in");
ofstream out("ninja2.out");

pair<int, int> segm[100000];

int main() {
	int n, m, k;
	in >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		int a, b;
		in >> a >> b;
		int d = (b - a) / 2 + 1;
		int m = (a + b) / 2;

		segm[i] = make_pair(m, d);
	}
	for (int i = 1; i <= k; ++i) {
		int a, b;
		in >> a >> b;
		int64 sum = 0;
 		for (int j = 1; j <= n; ++j) {
			if (a <= segm[j].first and segm[j].first <= b)
				sum += 1LL * min(segm[j].second,
					min(segm[j].first - a + 1, b - segm[j].first + 1));
		}
		out << sum << '\n';
	}
	in.close();
	out.close();
	return 0;
}
