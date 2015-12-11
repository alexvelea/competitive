#include <fstream>
#include <iostream>
using namespace std;

const int MOD = 9901;

ifstream in("fallingb.in");
ofstream out("fallingb.out");

int nr[125][1000];
int rez[125];

int l, add;

void bt(int p, int lst, int nxt) {
	if (p == 8) {
		nr[l + 1][nxt] += add;
		nr[l + 1][nxt] %= MOD;
		return ;
	}
	if (lst & (1 << p)) {
		bt(p + 1, lst, nxt);
		return ;
	}
    bt(p + 1, lst, nxt);
	if ((nxt & (1 << p)) == 0)
		bt(p + 1, lst, nxt | (1 << p));
 	if ((nxt & (1 << p)) == 0 and (nxt & (1 << (p+1))) == 0 and p + 1 < 8)
		bt(p + 1, lst, nxt | (1 << p) | (1 << (p + 1)));
 	if (p and (nxt & (1 << p)) == 0 and (nxt & (1 << (p-1))) == 0)
		bt(p + 1, lst, nxt | (1 << p) | (1 << (p - 1)));

	if ((lst & (1 << (p + 1))) or (p == 7))
		return ;
	bt(p + 2, lst, nxt);
	if ((nxt & (1 << p)) == 0)
		bt(p + 2, lst, nxt | (1 << p));
	if ((nxt & (1 << (p + 1))) == 0)
		bt(p + 2, lst, nxt | (1 << (p + 1)));
}

int bt_final(int p, int st) {
	if (p == 8)
		return 1;
	if (st & (1 << p))
		return bt_final(p + 1, st);
	if (p == 7)
		return 1;
	if (st & (1 << (p + 1)))
		return bt_final(p + 2, st);
	return bt_final(p + 1, st) + bt_final(p + 2, st);
}

int main() {
	nr[1][0] = 1;
    for (int i = 1; i <= 120; ++i) {
		// calculam rez[i]
		for (int j = 0; j < (1 << 8); ++j) {
			int f = bt_final(0, j);
			rez[i] += f * nr[i][j];
 			rez[i] %= MOD;
		}
		for (int j = 0; j < (1 << 8); ++j) {
			add = nr[i][j];
			l = i;
			bt(0, j, 0);
		}
	}

	int t;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		out << rez[m] << '\n';
	}
	return 0;
}
