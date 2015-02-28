#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("submatrix.in");
ofstream out("submatrix.out");

const int BufferSize = 100000;
char Buffer[BufferSize];
int BufferInd = BufferSize;
#define BufferC Buffer[BufferInd]
#define char_ok (((BufferC >= '0' and BufferC <= '9') or (BufferC == '-')) ? (1) : (0))
#define verf ((++BufferInd >= BufferSize) ? (in.read(Buffer, BufferSize), BufferInd = 0) : (1))

void cit(int &n) {
	verf;
	n = 0;
	bool sign = false;
	for (; not char_ok; verf)
		;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}

const int kMaxN = 305;

vector<int> Uniq;

int n, m, k;
int el[kMaxN][kMaxN];
int ap[kMaxN * kMaxN];

int rez = 0;

void solve(int l, int c) {
	int d = 0;
	for (int i = 0; i < int(Uniq.size()); ++i)
		ap[i] = 0;
	ap[el[l][c]] = 1;
 	int inside = 1;
	while (l + d < n and c + d < m) {
//        cerr << l << ' ' << c << ' ' << d << ' ' << inside << '\n';
		if (inside > k) {
			// facem--
 			for (int i = l; i <= l + d; ++i) {
				int e = el[i][c];
				ap[e]--;
				if (ap[e] == 0)
					inside--;
			}
			for (int j = c + 1; j <= c + d; ++j) {
				int e = el[l][j];
				ap[e]--;
				if (ap[e] == 0)
					inside--;
			}
			++l;
			++c;
			--d;
		} else {
        	rez = max(rez, d);
			++d;
			for (int i = l; i <= l + d; ++i) {
				int e = el[i][c + d];
				ap[e]++;
				if (ap[e] == 1)
					inside++;
			}
			for (int j = c; j < c + d; ++j) {
				int e = el[l + d][j];
				ap[e]++;
				if (ap[e] == 1)
					inside++;
			}
		}
	}
	if (inside <= k)
		rez = max(rez, d);
	return ;
}

int main() {
//	in >> n >> m >> k;
	cit(n); cit(m); cit(k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
//	    	in >> el[i][j];
			cit(el[i][j]);
			Uniq.push_back(el[i][j]);
		}
	
	sort(Uniq.begin(), Uniq.end());
	Uniq.resize(unique(Uniq.begin(), Uniq.end()) - Uniq.begin());
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			el[i][j] = lower_bound(Uniq.begin(), Uniq.end(), el[i][j]) - Uniq.begin();
	
	for (int c = 1; c <= m; ++c)
		solve(1, c);
	for (int l = 2; l <= n; ++l)
		solve(l, 1);

	out << rez + 1;
	in.close();
	out.close();
	return 0;
}
