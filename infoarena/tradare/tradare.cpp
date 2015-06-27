//Problem tradare from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxK = 100005;

ifstream fin("tradare.in");
ofstream fout("tradare.out");

vector<pair<int, int> > coord(7 * kMaxK);
vector<int> edge[4 * kMaxK];

bool viz[4 * kMaxK];

struct Segm {
	int l, c1, c2;
	Segm() {
		l = c1 = c2 = 0;
	}
	Segm(int _l, int _c1, int _c2) {
		l = _l;
		c1 = _c1;
        c2 = _c2;
	}
};

vector<Segm> segm(4 * kMaxK);

void addSegment(int l, int c1, int c2) {
	segm.push_back(Segm(l, c1, c2));
}

void addEdge(int a, int b) {
	edge[a].push_back(b);
	edge[b].push_back(a);
}

void df(int nod) {
	viz[nod] = true;
	for (auto itr : edge[nod]) {
		if (not viz[itr]) {
			df(itr);
		}
	}
}

int main() {
	segm.clear();
	coord.clear();
	int t; fin >> t;
	while (t--) {
		int n, m, k; fin >> n >> m >> k;

		for (int i = 1; i <= k; ++i) {
			int x, y; fin >> x >> y;
			coord.push_back(make_pair(x, y));
			
			coord.push_back(make_pair(x - 1, 0));
			coord.push_back(make_pair(x, 0));
			coord.push_back(make_pair(x + 1, 0));

 			coord.push_back(make_pair(x - 1, m + 1));
			coord.push_back(make_pair(x, m + 1));
			coord.push_back(make_pair(x + 1, m + 1));   		
		}
 		sort(coord.begin(), coord.end());
		coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
 		
		for (int ind = 0; ind < int(coord.size()); ) {
			while (ind < int(coord.size()) and (coord[ind].first == 0 or coord[ind].first == n + 1))
				++ind;
			int l = coord[ind].first, c = coord[ind].second;
			++ind;
			while (ind < int(coord.size()) and l == coord[ind].first) {
				if (coord[ind].second == c + 1) {
					++c;
				} else {
					addSegment(l, c + 1, coord[ind].second - 1);
					c = coord[ind].second;
				}
				++ind;
			}
		}

//		for (auto itr : segm) {
//			cerr << itr.l << '\t' << itr.c1 << '\t' << itr.c2 << '\n';
//		}

		int st = 0, now = 0, dr = 1;
		for (; now < int(segm.size()); ) {
			while (dr < int(segm.size()) and segm[now].l == segm[dr].l) {
				++dr;
			}

			
			int newNow = dr, begNow = now;
			while (now != 0 and now < newNow) {
 				if (segm[st].l + 1 != segm[now].l and (segm[st].c1 != 1 or segm[st].c2 != m or segm[now].c1 != 1 or segm[now].c1 != m)) {
					break;
				}

//				cerr << st << '\t' << now << "ST\n";
				while (st < begNow and segm[st].c2 < segm[now].c1) {
					++st;
				}
				if (st < begNow and segm[st].c1 <= segm[now].c1) {
					addEdge(st, now);
				}

 				while (st < begNow and segm[st].c2 < segm[now].c2) {
					++st;
				}
				if (st < begNow and segm[st].c1 <= segm[now].c2) {
					addEdge(st, now);
				}
				++now;
			}

 			if (dr == int(segm.size())) {
				break;
			}
 

			now = begNow;
			int lU = segm[dr].l;
			while (now < newNow) {
				
 				if (segm[dr].l - 1 != segm[now].l and (segm[dr].c1 != 1 or segm[dr].c2 != m or segm[now].c1 != 1 or segm[now].c1 != m)) {
					break;
				}   			

//				cerr << now << '\t' << dr << "DR\n";
				while (dr < int(segm.size()) and segm[dr].l == lU and segm[dr].c2 < segm[now].c1) {
					++dr;
				}
				if (dr < int(segm.size()) and segm[dr].l == lU and segm[dr].c1 <= segm[now].c1) {
					addEdge(dr, now);
				}

				while (dr < int(segm.size()) and segm[dr].l == lU and segm[dr].c2 < segm[now].c2) {
					++dr;
				}
				if (dr < int(segm.size()) and segm[dr].l == lU and segm[dr].c1 <= segm[now].c2) {
					addEdge(dr, now);
				}
				++now;
			}
		}
		
		df(0);

		bool ok = true;
		for (int i = 0; i < int(segm.size()); ++i) {
			if (not viz[i]) {
				ok = false;
			}
		}

		if (ok) {
			fout << "DA\n";
		} else {
			fout << "NU\n";
		}

		for (int i = 0; i < int(segm.size()); ++i) {
			edge[i].clear();
			viz[i] = false;
		}
		segm.clear();
		coord.clear();
	}
	return 0;
}
