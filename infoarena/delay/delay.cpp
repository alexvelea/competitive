#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it,v) for(vector<int> :: iterator it = (v).begin(); it != (v).end(); ++it)

const int max_n = 16005;

ifstream in("delay.in");
ofstream out("delay.out");

int n;

vector<int> vertex[max_n];
int poz_begin[max_n], poz_end[max_n], T[max_n], deep[max_n], ord;
bool viz[max_n];

int lca_poz[max_n];
pair<int, int> rmq[2*max_n][16];

void make_rmq() {
	for (int p = 1, P = 0; (1<<p) <= lca_poz[0]; ++p, ++P)
		for (int i = 1; i + (1<<p) - 1 <= lca_poz[0]; ++i) {
			rmq[i][p] = rmq[i][P];
			if (rmq[i+(1<<P)][P].first < rmq[i][p].first)
				rmq[i][p] = rmq[i+(1<<P)][P];
		}
}

int lca (int a, int b) {
	a = lca_poz[a];
	b = lca_poz[b];
	if (a > b)
		swap (a,b);
 	int d = b - a + 1;
	int p = 0;
	while ((1<<p) <= d)
		++p;
	--p;
	pair <int, int> l = rmq[b-(1<<p)+1][p];
	if (rmq[a][p].first < l.first)
		l = rmq[a][p];
	return l.second;
}

void df (int nod) {
	if (viz[nod])
		return ;
	viz[nod] = true;
 	poz_begin[nod] = ++ord;
	lca_poz[nod] = ++lca_poz[0];
	rmq[lca_poz[nod]][0] = make_pair (deep[nod], nod);
	FORIT (it, vertex[nod])
		if (!viz[*it]) {
			deep[*it] = deep[nod] + 1;
			df (*it);
			lca_poz[0]++;
			rmq[lca_poz[0]][0] = make_pair (deep[nod], nod);
		}
	poz_end[nod] = ++ord;
}

int aib[max_n];

void aib_update (int ind, int x) {
	while (ind <= ord) {
		aib[ind] += x;
		ind += ind & (-ind);
	}
	return ;
}
int aib_query (int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> T[i];
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back (b);
		vertex[b].push_back (a);
	}
	deep[1] = 1;	
	df (1);
	make_rmq();

//	for (int i = 1; i <= n; ++i) 
//		cerr << rmq[i][0].second << "$\n";
//		cerr << begin[i] << "\t" << end[i] << "\n";
	for (int i = 1; i <= n; ++i) {
		aib_update (poz_begin[i], T[i]);
		aib_update (poz_end[i], -T[i]);
	}
	int q;
	in >> q;
	while (q--) {
		int t, a, b;
		in >> t >> a >> b;
		if (t == 1) {
			int t = b;
			b -= T[a];
			T[a] = t;
			aib_update (poz_begin[a], b);
			aib_update (poz_end[a], -b);
		} else {
			int c = lca (a,b);
 			int rez = 0;
//			cerr << a << "%" << b << "\t" << c << "\n";
            rez += aib_query (poz_begin[a]);
			rez += aib_query (poz_begin[b]);
			rez -= 2*aib_query (poz_begin[c]);
			rez += T[c];
			out << rez << "\n";
		}
	}
	return 0;	
}

