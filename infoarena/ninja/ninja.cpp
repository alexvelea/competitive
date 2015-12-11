#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("ninja.in");
ofstream out("ninja.out");

const int kMaxN = 100005;

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


vector<int> segm[kMaxN];
vector<pair<int, int> > query_st[kMaxN], query_dr[kMaxN];

int64 rez[kMaxN];

struct Aint {
	int sum;
	int64 under;
	Aint () {
		sum = under = 0;
	}
} aint[4 * kMaxN];

void aint_clear(int nod, int st, int dr) {
	aint[nod].sum = 0;
	aint[nod].under = 0;
	if (st == dr)
		return ;
	int m = (st + dr) / 2;
	aint_clear(2 * nod, st, m);
	aint_clear(2 * nod + 1, m + 1, dr);
}

void aint_update(int nod, int st, int dr, int c1, int c2, int val) {
	if (c2 < st or dr < c1)
		return ;
	if (c1 <= st and dr <= c2) {
		aint[nod].sum += val;
		aint[nod].under += 1LL * (dr - st + 1) * val;
		return ;
	}
	int m = (st + dr) / 2;
	aint_update(2 * nod, st, m, c1, c2, val);
	aint_update(2 * nod + 1, m + 1, dr, c1, c2, val);
	aint[nod].under = 1LL * (aint[2 * nod].under + aint[2 * nod + 1].under + (dr - st + 1) * aint[nod].sum);
}

int64 aint_query(int nod, int st, int dr, int c1, int c2) {
	if (c2 < st or dr < c1)
		return 0;
	if (c1 <= st and dr <= c2)
		return aint[nod].under;
	int m = (st + dr) / 2;
	int64 rez = 0;
	rez += aint_query(2 * nod, st, m, c1, c2);
	rez += aint_query(2 * nod + 1, m + 1, dr, c1, c2);
	rez += 1LL * (aint[nod].sum * (min(dr, c2) - max(st, c1) + 1));
	return rez;
}

int main() {
	int n, m, k;
	cit(n);
	cit(m);
	cit(k);
	for (int i = 1; i <= n; ++i) {
		int a, b;
 		cit(a);
		cit(b);
		segm[(a + b) / 2].push_back((b - a) / 2 + 1);
	}
	
    for (int i = 1; i <= k; ++i) {
		int a, b;
		cit(a);
		cit(b);
		int m = (a + b) / 2;
		query_st[m].push_back(make_pair(a, i));
		if (m + 1 <= b)
			query_dr[m + 1].push_back(make_pair(b, i));
	}

	for (int i = 1; i <= m; ++i)
		for (int rhs : segm[i])
			aint_update(1, 1, m, i - rhs + 1, i, +1);

	for (int i = m; i; --i) {
		for (pair<int, int> rhs : query_st[i]) {
			rez[rhs.second] += aint_query(1, 1, m, rhs.first, i);
		}
		for (int rhs : segm[i])
			aint_update(1, 1, m, i - rhs + 1, i, -1);
	}
	aint_clear(1, 1, m);

 	for (int i = 1; i <= m; ++i)
		for (int rhs : segm[i])
			aint_update(1, 1, m, i, i + rhs - 1, +1);

	for (int i = 1; i <= m; ++i) {
		for (pair<int, int> rhs : query_dr[i]) {
			rez[rhs.second] += aint_query(1, 1, m, i, rhs.first);
		}
		for (int rhs : segm[i])
			aint_update(1, 1, m, i, i + rhs - 1, -1);
	}   

	for (int i = 1; i <= k; ++i)
		out << rez[i] << '\n';
	in.close();
	out.close();
	return 0;
}
