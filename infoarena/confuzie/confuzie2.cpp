#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 200005, inf = 0x3f3f3f3f;

ifstream in("confuzie.in");
ofstream out("confuzie.out");

#define kMaxChar 1000000
#define verf ((++BufferChar >= kMaxChar) ? (in.read(Buffer, kMaxChar), BufferChar = 0) : (1))

int BufferChar = kMaxChar;
char Buffer[kMaxChar];

void cit (int &a) {
    if (BufferChar >= kMaxChar)
        verf;
    bool minus = false;
    for ( ;!((Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9') || (Buffer [BufferChar] == '-')); verf)
        ;
    if (Buffer[BufferChar] == '-') {
        verf;
        minus = true;
    }
    for (a = 0; (Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9'); a *= 10,a += (Buffer[BufferChar] - '0'), verf)
        ;
    if (minus)
        a *= -1;
    return ;
}

bool viz[kMaxN], black[kMaxN];

int begin_ind[kMaxN], end_ind[kMaxN], ind_nod[2 * kMaxN], ind;
vector<int> vertex[kMaxN];

void df(int nod) {
	begin_ind[nod] = ++ind;
	ind_nod[ind] = nod;
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (not viz[oth]) {
			df(oth);
		}
	}
	end_ind[nod] = ++ind;
	ind_nod[ind] = nod;
}

struct AintNode{
	int sum, min, poz;
} aint[4 * kMaxN * 2];

void aint_update(int nod, int st, int dr, int c, int val) {
 	if (st == dr) {
		aint[nod].sum = aint[nod].min = val;
		aint[nod].poz = st;
		return ;
	}
	int m = (st + dr) / 2;
 	if (c <= m)
		aint_update(2 * nod, st, m, c, val);
	else
		aint_update(2 * nod + 1, m + 1, dr, c, val);

	aint[nod].sum = aint[2 * nod].sum + aint[2 * nod + 1].sum;
	if (aint[2 * nod].min <= aint[2 * nod].sum + aint[2 * nod + 1].min) {
		aint[nod].min = aint[2 * nod].min;
		aint[nod].poz = aint[2 * nod].poz;
	} else {
		aint[nod].min = aint[2 * nod + 1].min + aint[2 * nod].sum;
		aint[nod].poz = aint[2 * nod + 1].poz;
	}
	return ;
}

pair<int, int> aint_query(int nod, int st, int dr, int c1, int c2) {
	if (c1 <= st and dr <= c2) 
		return make_pair(aint[nod].min, aint[nod].poz);
	if (c2 < st or dr < c1)
		return make_pair(inf, 0);
	
	pair<int, int> a, b;
	int m = (st + dr) / 2;
	a = aint_query(2 * nod, st, m, c1, c2);
	b = aint_query(2 * nod + 1, m + 1, dr, c1, c2);
	b.first += aint[2 * nod].sum;
	if (a > b)
		a = b;
	return a;
}

void aint_make(int nod, int st, int dr) {
	aint[nod].poz = st;
	if (st == dr)
		return ;
	int m = (st + dr) / 2;
	aint_make(2 * nod, st, m);
	aint_make(2 * nod + 1, m + 1, dr);
}

int main() {
	int n, q;
	cit(n); cit(q);
	aint_make(1, 1, 2 * n);
	for (int i = 1; i < n; ++i) {
		int a, b;
		cit(a); cit(b);
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	df(1);
	ind_nod[0] = -1;
	while (q--) {
		int t;
		cit(t);
		if (t == 0) {
			int x;
			cit(x);
			black[x] ^= 1;
			aint_update(1, 1, 2 * n, begin_ind[x], (black[x] == 1) ? (+1) : (0));
 			aint_update(1, 1, 2 * n, end_ind[x], (black[x] == 1) ? (-1) : (0));   		
		} else {
			int x, y;
			cit(x); cit(y);
			pair<int, int> rez;
			rez = aint_query(1, 1, 2 * n, end_ind[y], end_ind[x]);
//			cerr << end_ind[y] << '\t' << end_ind[x] << '\n';
//			cerr << rez.first << '\t' << rez.second << "\n\n";
//			cerr << black[y] << '\n';
			if (ind_nod[rez.second] == y and black[y] == false) {
				out << "-1\n";
				continue;
			}

			out << ind_nod[rez.second] << '\n';
		}
	}
	return 0;
}
