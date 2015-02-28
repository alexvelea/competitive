#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

const int kMaxN = 1000005;

vector<int> L[kMaxN], C[kMaxN], el[kMaxN];

int n, m, r;

int aint_query_begin(vector<int> &aint, int nod, int st, int dr, int val) {
//	cerr << st << '\t' << dr << '\t' << aint[nod] << '\n';
	if (st == dr) {
		aint[nod] = 0;
		return st;
	} else {
        if (aint[nod] < val)
			return 0;

		int m = (st + dr) / 2;
		int rez = 0;
		if (aint[2 * nod] >= val)
			rez = aint_query_begin(aint, 2 * nod, st, m, val);
		else
			rez = aint_query_begin(aint, 2 * nod + 1, m + 1, dr, val);
		aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
		return rez;
	}
}

int aint_query_end(vector<int> &aint, int nod, int st, int dr, int val) {
	if (st == dr) {
		aint[nod] = 0;
		return st;
	} else {
        if (aint[nod] < val)
			return 0;

		int m = (st + dr) / 2;
		int rez = 0;
		if (aint[2 * nod + 1] >= val)
 			rez = aint_query_end(aint, 2 * nod + 1, m + 1, dr, val);   		
		else
 			rez = aint_query_end(aint, 2 * nod, st, m, val);
		aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
		return rez;
	}
}

void aint_update(vector<int> &aint, int nod, int st, int dr, int c, int val) {
	if (st == dr) {
		aint[nod] = val;	
	} else {
		int m = (st + dr) / 2;
		if (c <= m)
			aint_update(aint, 2 * nod, st, m, c, val);
		else
			aint_update(aint, 2 * nod + 1, m + 1, dr, c, val);
		aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
	}
}

void update(int x, int y) {
	aint_update(L[x], 1, 1, m, y, el[x][y]);
	aint_update(C[y], 1, 1, n, x, el[x][y]);
}

int main() {
	int r, k, p;
	in >> n >> m >> r >> k >> p;

	for (int i = 1; i <= n; ++i) {
		L[i].resize(4 * m + 3);
		el[i].resize(m + 1);
	}

	for (int i = 1; i <= m; ++i)
		C[i].resize(4 * n + 3);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			in >> el[i][j];
			update(i, j);
		}
	
	while (k--) {
		char c;
		int l, val;
		in >> c >> l >> val;
		vector<pair<int, int> > Coord;
		for (int i = 1; i <= r; ++i) {
			int coord = 0;
			if (c == 'N')
				coord = aint_query_begin(C[l], 1, 1, n, val);
			if (c == 'S')
				coord = aint_query_end(C[l], 1, 1, n, val);
			if (c == 'W')
				coord = aint_query_begin(L[l], 1, 1, m, val);
			if (c == 'E')
				coord = aint_query_end(L[l], 1, 1, m, val);
			if (coord != 0) {
				if (c == 'N' or c == 'S')
					Coord.push_back(make_pair(coord, l));
				else
					Coord.push_back(make_pair(l, coord));
			}
//			cerr << coord << "!\n";
		}
		
		for (pair<int, int> itr : Coord) {
			el[itr.first][itr.second]--;
			update(itr.first, itr.second);
		}
	}
 	
//	for (int i = 1; i <= n; ++i, cerr << '\n')
//		for (int j = 1; j <= m; ++j)
//			cerr << el[i][j] << ' ';

	int mx = 0;
	for (int i = 1; i + p - 1 <= n; ++i)
		for (int j = 1; j + p - 1 <= m; ++j) {
			int sum = 0;
			for (int l = 0; l < p; ++l)
				for (int c = 0; c < p; ++c) 
					sum += el[i + l][j + c];
			if (sum > mx)
				mx = sum;
		}
	out << mx << '\n';

	return 0;
}
