//Problem invazia from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 300005;

ifstream in("invazia.in");
ofstream out("invazia.out");

struct AintNode {
	int min;
	AintNode *left, *right;
	AintNode() {
		left = right = NULL;
		min = inf;
	}
};

AintNode* aintUpdate(AintNode *nod, int st, int dr, int c1, int c2, int h) {
	if (dr < c1 or c2 < st) {
		return nod;
	}
	if (nod == NULL) {
		nod = new AintNode;
	}
	AintNode *rez = new AintNode;
	rez->min = nod->min;
	if (c1 <= st and dr <= c2) {
		if (h > nod->min) {
			delete rez;
			return nod;
		}

		rez->min = min(h, rez->min);
		rez->left = nod->left;
		rez->right = nod->right;
		return rez;
	}
	int m = (st + dr) / 2;
    rez->left = aintUpdate(nod->left, st, m, c1, c2, h);
	rez->right = aintUpdate(nod->right, m + 1, dr, c1, c2, h);
	return rez;
}

int aintQuery(AintNode *nod, int x, int y, int poz) {
	if (nod == NULL) {
		return inf;
	}

	int rez = nod->min;
	if (x == y) {
		return rez;
	}
	int m = (x + y) / 2;
	if (poz <= m) {
		rez = min(aintQuery(nod->left, x, m, poz), rez);
	} else {
		rez = min(aintQuery(nod->right, m + 1, y, poz), rez);
	}
	return rez;
}

int main() {
	int n, m;
	stack<AintNode*> ships;
	ships.push(new AintNode);
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		char c;
		in >> c;
		if (c == 'I') {
			int st, dr, h;
			in >> st >> dr >> h;
			ships.push(aintUpdate(ships.top(), 1, n, st, dr, h));
		}  else if (c == 'E') {
			ships.pop();
		} else {
			int poz;
			in >> poz;
			int r = aintQuery(ships.top(), 1, n, poz);
			if (r == +inf) {
				out << "GUITZZZ!\n";
			} else {
				out << r << '\n';
			}
		}
	}
	return 0;
}
