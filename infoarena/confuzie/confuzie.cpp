#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("confuzie.in");
ofstream out("confuzie.out");

const int inf = 0x3f3f3f3f, kMaxN = 200005;

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


int n;
vector<int> vertex[kMaxN];
int parent[20][kMaxN];
int enter_id[kMaxN], exit_id[kMaxN], ind;
bool black[kMaxN], viz[kMaxN];

int aib[2 * kMaxN];

int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}

void aib_update(int ind, int val) {
	while (ind <= 2 * n) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
	return ;
}

void df(int nod) {
	viz[nod] = true;
	enter_id[nod] = ++ind;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		if (not viz[vertex[nod][i]]) {
			parent[0][vertex[nod][i]] = nod;
			df(vertex[nod][i]);
		}
	}
	exit_id[nod] = ++ind;
}


int main() {
	int q;
    cit(n);
    cit(q);
	for (int i = 1; i < n; ++i) {
		int a, b;
        cit(a);
        cit(b);
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	df(1);
	for (int l = 1; 1 << l <= n; ++l)
		for (int i = 1; i <= n; ++i)
			parent[l][i] = parent[l - 1][parent[l - 1][i]];
	while (q--) {
		int t;
        cit(t);
		if (t == 0) {
			int x;
            cit(x);
			black[x] ^= 1;
			aib_update(enter_id[x], (black[x] == 1) ? (+1) : (-1));
			aib_update(exit_id[x], (black[x] == 1) ? (-1) : (+1));
		} else {
			int x, y;
            cit(x);
            cit(y);
			x = parent[0][x];
			int p = 19;
			int k = aib_query(enter_id[x]);
			if (aib_query(enter_id[y]) == k) {
				out << "-1\n";
				continue;
			}

			for (; p >= 0; --p) {
				if (aib_query(enter_id[parent[p][y]]) > k)
					y = parent[p][y];
			}

			out << y << '\n';
		}
	}
    return 0;
}
