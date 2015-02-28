#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int max_n = 50005;

ifstream in("distante.in");
ofstream out("distante.out");

#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    bool ok=0;
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
    if ( Buffer[ CharB ] == '-' ){
        verf;
        ok=1;
    }
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}

queue<int> bfs;
int n, m, s;
vector<pair<int,int> > vertex[max_n];
int best[max_n];

bool viz[max_n];

int main() {
	verf;
	int t;
//	in >> t;
	cit (t);
	while (t--) {
		cit (n);
		cit (m);
		cit (s);
//    	in >> n >> m >> s;
		for (int i = 1; i <= n; ++i) {
			viz[i] = 0;
			vertex[i].clear();
		}
		for (int i = 1; i <= n; ++i)
//			in >> best[i];
			cit (best[i]);
		for (int i = 1; i <= m; ++i) {
			int a, b, c;
//			in >> a >> b >> c;
			cit (a);
			cit (b);
			cit (c);
			vertex[a].push_back(make_pair(b, c));
			vertex[b].push_back(make_pair(a, c));
		}
		bool ok = true;
		if (best[s] != 0)
			ok = false;
		best[s] = 0;
		while (bfs.size())
			bfs.pop();
		bfs.push(s);
		viz[s] = true;
		while (bfs.size()) {
			int nod = bfs.front();
 			bfs.pop();
			for (int i = 0; i < int(vertex[nod].size()); ++i) {
				if (viz[vertex[nod][i].first])
					continue;
 				if (best[vertex[nod][i].first] == best[nod] + vertex[nod][i].second) {
					viz[vertex[nod][i].first] = true;
					bfs.push(vertex[nod][i].first);
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			if (viz[i] == 0)
 				ok = false;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < int(vertex[i].size()); ++j)
				if (best[vertex[i][j].first] > best[i] + vertex[i][j].second)
					ok = false;
 		if (ok)
			out << "DA\n";
		else
			out << "NU\n";
	}
	return 0;
}
