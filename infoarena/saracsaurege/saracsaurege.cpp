//Problem saracsaurege from Infoarena
// "We are drowning in information and starved for knowledge."
#include <fstream>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 50005;

ifstream in("saracsaurege.in");
ofstream out("saracsaurege.out");

int rmq[kMaxN], oldRmq[kMaxN], init[kMaxN];
int n, l;

void upgradeRmq() {
	for (int i = 1; i <= n; ++i)
		oldRmq[i] = rmq[i];
	for (int i = 1; i <= n; ++i)
		if (i + l <= n)
			rmq[i] = max(oldRmq[i], oldRmq[i + l]);
	l *= 2;
}

int main() {
	int m;
	in >> n >> m;

	l = 1;
	for (int i = 1; i <= n; ++i) {
		in >> init[i];
		rmq[i] = init[i];
	}

	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		
		if (a + l > b) {
			l = 1;
			for (int j = 1; j <= n; ++j)
				rmq[j] = init[j];
		}

		while (b - a > 2 * l)
			upgradeRmq();
//		for (int j = 1; j <= n; ++j)
//			out << rmq[j] << '\t';
//		out << '\n';
		out << max(rmq[a], rmq[b - l + 1]) << '\n';
	}
	return 0;
}
