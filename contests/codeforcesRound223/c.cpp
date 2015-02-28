#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int kMaxN = 1000005;

int aint[8*kMaxN];
int sum[kMaxN], el[kMaxN];
string T;

void make_aint(int nod, int st, int dr) {
 	if (st == dr) 
		aint[nod] = sum[st];
	else {
		int m = (st + dr) / 2;
		make_aint(2 * nod, st, m);
		make_aint(2 * nod + 1, m + 1, dr);
		aint[nod] = min(aint[2 * nod], aint[2 * nod + 1]);
	}
}

int aint_query(int nod, int st, int dr, int c1, int c2) {
	if (dr < c1 or c2 < st)
		return 0x3f3f3f3f;
	if (st == dr) 
		return aint[nod];
	
	if (c1 <= st and dr <= c2) {
		return aint[nod];
	} else {
		int m =(st + dr) / 2;
		return min(
			aint_query(2 * nod, st, m, c1, c2), 
			aint_query(2 * nod + 1, m + 1, dr, c1, c2)
		);
	}
}

int main() {
	cin >> T;
	int n = T.size();
	for (int i = 0; i < n; ++i)
		if (T[i] == '(') {
			el[i + 1] = +1;
		} else {
			el[i + 1] = -1;
		}
	for (int i = 1; i <= n; ++i) 
		sum[i] = sum[i - 1] + el[i];
 	make_aint(1, 1, n);
	int m;
	cin >> m;
	while (m--) {
		int st, dr;
		cin >> st >> dr;
		int x = aint_query(1, 1, n, st, dr);
		int add = sum[st - 1] - x;
		if (add < 0)
			add = 0;
		int y = sum[dr] + add - sum[st - 1];
 		cout << dr - st + 1 - y - add << ' ';
	}
	return 0;
}
