//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("arbciclu.in");
ofstream out("arbciclu.out");

const int kMaxN = 100005;;

map<int, int> edge[kMaxN];
int degree[kMaxN];
bool deleted[kMaxN], inside[kMaxN];
int stv[kMaxN], dr;

const int kBufferSize = 10000;
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


int main() {
	int t;
    cit(t);
	while (t--) {
		int n, m;
        cit(n);
        cit(m);

        for (int i = 1; i <= n; ++i) {
			edge[i].clear();
			degree[i] = 0;
			deleted[i] = false;
			inside[i] = false;
		}

		while (m--) {
			int a, b;
            cit(a);
            cit(b);
			edge[a][b] = true;
			edge[b][a] = true;
			degree[a]++;
			degree[b]++;
		}

		dr = 0;
	
		bool bad = false;

		if (n < 3)
			bad = true;

		for (int i = 1; i <= n; ++i) {
			if (degree[i] == 2) {
				stv[++dr] = i;
				inside[i] = true;
			}

			if (degree[i] == 1)
				bad = true;
		}

		if (bad) {
			out << "NO\n";
			continue;
		}

		while (dr) {
			int nod = stv[dr--];
			if (deleted[nod] == true or degree[nod] != 2)
				continue;

 			vector<int> el;
			for (pair<int, bool> itr : edge[nod]) {
				if (not deleted[itr.first] and itr.second == true)
					el.push_back(itr.first);
			}

//			sort(el.begin(), el.end());
//			el.resize(unique(el.begin(), el-end()) - el.begin());

			deleted[nod] = true;
			int a = el[0], b = el[1];

			degree[a]--;
			degree[b]--;

			if (edge[a][b] != true) {
				edge[a][b] = true;
				edge[b][a] = true;
				degree[a]++;
				degree[b]++;
			}

			for (int itr : el) {
				if (degree[itr] == 2 and not inside[itr]) {
					inside[itr] = true;
					stv[++dr] = itr;
				}
			}
		}
		int left = n;
		for (int i = 1; i <= n; ++i)
			left -= deleted[i];

		if (left != 2) {
			out << "NO\n";
		} else {
			out << "YES\n";
		}
	}
    return 0;
}
