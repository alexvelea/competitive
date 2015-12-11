#include <cassert>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

const int max_n=1005;

ifstream in("amici.in");
ofstream out("amici.out");

int P[max_n], rez[max_n];
bool M[max_n][max_n];

int t, n, m;
int a, b;
int st, dr;


int next( int i ){
	if( i == n )
		return 1;
	return i+1;
}
int prev( int i ){
	if( i == 1 )
		return n;
	return i-1;
}

int main(){
	for (in >> t; t; --t) {
	    in >> n >> m;
		for (int i=1; i<=n; ++i)
			for (int j=i+1; j<=n; ++j)
				M[i][j] = M[j][i] = true;
		while ( m--) {
			in >> a >> b;
			M[a][b] = M[b][a] = false;
		}
		for (int i=1; i<=n; ++i ){
			P[i] = i;
		}
		int ok;
		do {
		ok = false;
		for (int i=1; i<=n; ++i)
			if( not M[P[i]][P[next(i)]]){
				ok = true;
				int init = 0;
				for (int j = 1; j <= n; ++j)
					init += M[P[j]][P[next(j)]];

				int a = P[i];
				int b = P[next(i)];
				int j = next(i);
				int l = 1;
				while (not(M[a][P[j]] && M[b][P[next(j)]])) {
					j = next(j);
					++l;
				}
				assert (l <= n-2);

				int st = next(i);
				int dr = j;
				for (l = l / 2; l; --l) {
					swap (P[st], P[dr]);
					st = next(st);
					dr = prev(dr);
				}
				int now = 0;
				for (int j = 1; j <= n; ++j)
					now += M[P[j]][P[next(j)]];
				assert (now > init);
			}
		}while(ok);
		for (int i = 1; i <= n; ++i) 
			rez[P[i]] = P[next(i)];
		for (int i = 1; i <= n; ++i)
			out << rez[i] << " ";
		out << "\n";
	}
	return 0;
}
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

ifstream in("amici.in");
ofstream out("amici.out");

const int inf = 0x3f3f3f3f;

int main() {

    return 0;
}
