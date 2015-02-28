#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("revolutie.in");
ofstream out("revolutie.out");

const int kMaxN = 130;

vector<int> vertex[kMaxN];
vector<pair<int, int> > rez;
bool viz[kMaxN];
int st[kMaxN], dr[kMaxN], nr_c;
int where[kMaxN], here[kMaxN], to[kMaxN];

bool aug_path(int nod) {
	viz[nod] = true;
	for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
		int oth = vertex[nod][itr];
		if (dr[oth] == 0) {
			dr[oth] = nod;
			st[nod] = oth;
			return true;
		}
	}

	for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
		int oth = vertex[nod][itr];
		if (not viz[dr[oth]] and aug_path(dr[oth])) {
			st[nod] = oth;
			dr[oth] = nod;
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int e;
			in >> e;
			if (e)
				vertex[i].push_back(j);
		}
	bool ok = true;
	while (ok) {
		ok = false;
		for (int i = 1; i <= n; ++i)
			viz[i] = false;
		for (int i = 1; i <= n; ++i)
			if (not viz[i] and st[i] == 0 and aug_path(i)) {
				++nr_c;
				ok = true;
			}
	}

	if (nr_c != n)
		out << "-1\n";
	else {
		for (int i = 1; i <= n; ++i) {
			where[i] = i;
			to[dr[i]] = i;
			here[i] = i;
		}
		for (int i = 1; i <= n; ++i)
			if (where[i] != to[i]) {
				int a = where[i];
				int b = to[i];
				int A = here[a];
				int B = here[b];
 	   			rez.push_back(make_pair(a, b));
    			swap(here[a], here[b]);
				where[A] = b;
				where[B] = a;
			}
		out << rez.size() << '\n';
		for (int itr = 0; itr < int(rez.size()); ++itr)
			out << "L " << rez[itr].first << ' ' << rez[itr].second << '\n';
	}
	in.close();
	out.close();
	return 0;
}
