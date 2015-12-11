#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

ifstream in("poze.in");
ofstream out("poze.out");

const int kBufferSize = 1000005;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (in.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;
	
	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
    
	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}


const int kMaxN = 305;

int order[10][kMaxN][kMaxN];
int el[kMaxN][kMaxN];
int n, m, k, lg;

vector<pair<int, pair<int, int> > > ord;

struct SuffixNode {
	int val[4], x, y;
	SuffixNode() {
		val[0] = val[1] = val[2] = val[3] = 0;
		x = y = 0;
	}


	int get_order(int x, int y, int lg) {
		if (x <= n and y <= m)
			return order[lg][x][y];
		return -1;
	}

	SuffixNode(int _x, int _y, int lg) {
		x = _x;
		y = _y;
 		val[0] = get_order(x, y, lg);
		val[2] = get_order(x + (1 << lg), y, lg);
		val[1] = get_order(x, y + (1 << lg), lg);
		val[3] = get_order(x + (1 << lg), y + (1 << lg), lg);
	}
	bool operator == (const SuffixNode &rhs) const {
		for (int i = 0; i < 4; ++i)
			if (val[i] != rhs.val[i])
				return false;
		return true;
	}
	bool operator < (const SuffixNode &rhs) const {
		for (int i = 0; i < 4; ++i)
			if (val[i] != rhs.val[i])
				return val[i] < rhs.val[i];
		return 0;
	}
};

struct LCP {
	int val[4];
	
 	LCP() {
		val[0] = val[1] = val[2] = val[3] = 0;
	}
	LCP(int x, int y, int d, int l) {
		int L = 1 << l;
		val[0] = order[l][x][y];
		val[1] = order[l][x + d - L][y];
		val[2] = order[l][x][y + d - L];
		val[3] = order[l][x + d - L][y + d - L];
	}

 	int64 hash() {
		int64 rez = 0;
		for (int i = 0; i < 4; ++i)
			rez += 1LL * (1LL << (i * 15)) * val[i];
		return rez;
	}
 

	bool operator == (const LCP &rhs) const {
		for (int i = 0; i < 4; ++i)
			if (val[i] != rhs.val[i])
				return false;
		return true;
	}

	bool operator < (const LCP &rhs) const {
		for (int i = 0; i < 4; ++i)
			if (val[i] != rhs.val[i])
				return val[i] < rhs.val[i];
		return false;
	}
};

//vector<LCP> lcp;
unordered_map<int64, int> lcp;
vector<SuffixNode> query;

int main() {
	int  t;
	cit(t);
	while (t--) {
		cit(n);
		cit(m);
		cit(k);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				cit(el[i][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				order[0][i][j] = el[i][j];
		lg = 1;
 		for (; (1 << lg) <= min(n, m); ++lg) {
			query.clear();
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j)
					query.push_back(SuffixNode(i, j, lg - 1));
			sort(query.begin(), query.end());
			int ind = 1;
			for (int st = 0; st < int(query.size()); ++st) {
            	if (st and not (query[st] == query[st - 1]))
					++ind;
				order[lg][query[st].x][query[st].y] = ind;
			}
		}
		--lg;
		ord.clear();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				ord.push_back(make_pair(order[lg][i][j], make_pair(i, j)));
		
		sort(ord.begin(), ord.end());
 		int rez = 0, l = lg;
		int mx = 0;
		for (; l >= 0; --l) {
			int d = rez + (1 << l), L = max(mx, l);
			
			lcp.clear();
			bool ok = false;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m and not ok; ++j) 
					if (i + d - 1 <= n and j + d - 1 <= m) {
						int64 x = LCP(i, j, d, L).hash();
 						lcp[x]++;
						if (lcp[x] >= k)
							ok = true;
					}

			int p = 0, act = 0;
/* 			sort(lcp.begin(), lcp.end());   		
			for (int st = 0; st < int(lcp.size()); ++st) {
            	if (st and not (lcp[st - 1] == lcp[st]))
					act = 0;
				act++;
				if (act > p)
					p = act;
			}*/

//			if (p >= k) {
			if (ok) {
				rez += (1 << l);
				mx = max(mx, l);
			}
		}
		out << rez << '\n';
	}
    return 0;
}
