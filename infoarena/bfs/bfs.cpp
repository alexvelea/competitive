#include <cmath>

#include <algorithm>
#include <fstream>
#include <queue>
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

ifstream in("bfs.in");
ofstream out("bfs.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005;

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



int n;
vector<int> vertex[kMaxN];
int best[kMaxN];

void bfs(int start) {
	for (int i = 1; i <= n; ++i)
		best[i] = inf;

	best[start] = 0;

	queue<int> bfs;
	bfs.push(start);

	while (bfs.size()) {
		int nod = bfs.front();
		bfs.pop();
		for (int i = 0; i < int(vertex[nod].size()); ++i) {
			int oth = vertex[nod][i];
			if (best[nod] + 1 < best[oth]) {
				best[oth] = best[nod] + 1;
				bfs.push(oth);
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		best[i] = (best[i] != inf) ? (best[i]) : (-1);
}

int main() {
	int m, s;
	cit(n); cit(m); cit(s);
    while (m--) {
		int a, b;
		cit(a); cit(b);
		vertex[a].push_back(b);
	}

	bfs(s);

	for (int i = 1; i <= n; ++i)
		out << best[i] << ' ';
	return 0;
}
