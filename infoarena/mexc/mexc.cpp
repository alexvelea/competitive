#include <algorithm>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second

ifstream in("mexc.in");
ofstream out("mexc.out");

#define MaxChar 1000000
#define verf ( (++CharB >= MaxChar) ? (in.read(Buffer, MaxChar), CharB = 0) : (1))

long CharB = MaxChar;
char Buffer[MaxChar];

void cit (int &a) {
	if (CharB >= MaxChar)
		verf;
    bool ok=0;
    for ( ; !((Buffer[CharB] >= '0' && Buffer[CharB] <= '9') || (Buffer [CharB] == '-')); verf)
        ;
    if (Buffer[CharB] == '-') {
        verf;
        ok=1;
    }
    for (a = 0; (Buffer[CharB] >= '0' && Buffer[CharB] <= '9'); a *= 10,a += (Buffer[CharB] - '0'), verf)
        ;
    if (ok) {
        a=-a;
    }
}


const int kMaxN = 805, inf = 0x3f3f3f3f;

int el[kMaxN][kMaxN], final_rez[kMaxN][kMaxN];
int n, m, d, nr_f;
int father[kMaxN][kMaxN], rez[kMaxN * kMaxN], p[kMaxN * kMaxN];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

vector<pair<int, int> > x;

bool el_sort(pair<int, int> a, pair<int, int> b) {
	return el[a.fi][a.se] > el[b.fi][b.se];
}

int get_father(int x) {
	if (p[x] != x)
		p[x] = get_father(p[x]);
	return p[x];
}

int get_father(int x, int y) {
	if (father[x][y] == 0)
		return 0;
	father[x][y] = get_father(father[x][y]);
	return father[x][y];
}                      

int unite(int a, int b) {
	if (a == 0 or b == 0)
		return max(a, b);
	a = get_father(a);
	b = get_father(b);

	if (a == b)
		return a;

	int x = rand() % 2;
	if (x == 1)
		swap(a, b);

	p[b] = a;
	rez[a] += rez[b];
	rez[b] = 0;
	return a;
}


int main() {
    cit(n);
    cit(m);
    cit(d);
	srand(time(NULL));
 	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
            cit(el[i][j]);
			x.push_back(make_pair(i, j));
		}
	sort(x.begin(), x.end(), el_sort);
 	for (int i1 = 0, i2 = 0; i1 < int(x.size()) or i2 < int(x.size()); ) {
		int mx = -inf;
		if (i1 < int(x.size()))
			mx = el[x[i1].fi][x[i1].se] + d;
		if (i2 < int(x.size()) and mx <= el[x[i2].fi][x[i2].se]) {
			mx = el[x[i2].fi][x[i2].se];
		} else {
			mx = el[x[i2].fi][x[i2].se] +1;
		}
 		while (i1 < int(x.size()) and el[x[i1].fi][x[i1].se] + d >= mx) {

			int a = 0;
			for (int d = 0; d < 4; ++d) {
				int nx = x[i1].fi + dx[d];
				int ny = x[i1].se + dy[d];
				if (a == 0)
					a = get_father(nx, ny);
				else {
					get_father(nx, ny);
					a = unite(a, father[nx][ny]);
				}
			}
			if (a == 0) {
 				++nr_f;
				father[x[i1].fi][x[i1].se] = nr_f;
				p[nr_f] = nr_f;   		
			} else {
				father[x[i1].fi][x[i1].se] = a;
			}
			++i1;
		}
		int c = i2;
		while (i2 < int(x.size()) and el[x[i2].fi][x[i2].se] >= mx) {
			int f = get_father(x[i2].fi, x[i2].se);
			rez[f]++;
			++i2;
		}

		i2 = c;
 		while (i2 < int(x.size()) and el[x[i2].fi][x[i2].se] >= mx) {
			int f = get_father(x[i2].fi, x[i2].se);
			final_rez[x[i2].fi][x[i2].se] = rez[f];
			++i2;
		}
	}
	for (int i = 1; i <= n; ++i, out << '\n')
		for (int j = 1; j <= m; ++j)
			out << final_rez[i][j] << ' ';
	return 0;
}
