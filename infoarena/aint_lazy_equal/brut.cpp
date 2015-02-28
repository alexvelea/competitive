#include <fstream>
using namespace std;

#define int64 long long

ifstream in("aint_lazy_equal.in");
ofstream out("date.out");

const int kMaxN = 100005;

int el[kMaxN];

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	while (m--) {
		int t;
		in >> t;
		if (t == 1) {
			int x, y, val;
			in >> x >> y >> val;
			while (x <= y)
				el[x++] = val;
		} else {
			int64 rez = 0;
			int x, y;
			in >> x >> y;
			while (x <= y)
				rez += el[x++];
			out << rez << '\n';
		}
	}
	in.close();
	out.close();
	return 0;
}
