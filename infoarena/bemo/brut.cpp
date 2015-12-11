#include <fstream>
using namespace std;

const int kMaxN = 1505;

ifstream in("bemo.in");
ofstream out("bemo2.out");

pair<int, int> poz[kMaxN * kMaxN];
int rez[2 * kMaxN];

int n, m;

int main() {
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int el;
			in >> el;
			poz[el] = make_pair(i, j);
		}
	in.close();
	poz[n * m + 1] = make_pair(n + 1, m + 1);
	rez[n + m] = n * m + 1;
	for (int i = 1; i <= n * m; ++i) {
		int nr = poz[i].first + poz[i].second - 1;
		if (rez[nr])
			continue;
		int st = nr, dr = nr;
		while (st > 0 and not rez[st])
			--st;
		while (dr < n * m and not rez[dr])
			++dr;
		if (poz[rez[st]].first <= poz[i].first and 
			poz[rez[st]].second <= poz[i].second and 
			poz[i].first <= poz[rez[dr]].first and
			poz[i].second <= poz[rez[dr]].second) {
				rez[nr] = i;
			}
	}
	for (int i = 1; i < n + m; ++i)
		out << rez[i] << ' ';
	out.close();
	return 0;
}
