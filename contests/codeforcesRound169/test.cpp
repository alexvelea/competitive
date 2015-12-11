#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it,v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
const int nr = 8;

vector< vector<int> > final;
vector<int> el[nr/2];


void unic (vector<int> a) {
	bool bad = false;
	for (int i = 0; i < int(final.size()); ++i) {
		int ok = true;
		for (int j = 0; j < nr; ++j) {
			if (a[j] != final[i][j])
				ok = false;
		}
		if (ok == true)
			bad = true;
	}
	if (bad == false) {
		final.push_back(a);
	}
	return ;
}

void solve (int x) {
	if (x == nr) {
		// totul e ok
 		for (int i = 0; i < nr/2; ++i)
			if (el[i][0] > el[i][1])
				swap (el[i][0], el[i][1]);
		int viz[nr];
 		for (int i = 0; i < nr; ++i)
			viz[i] = 0;
		for (int i = 0; i < nr/2; ++i)
			viz[el[i][0]] = el[i][1];
		vector<int> rez;
 		for (int i = 0; i < nr; ++i)
			if (viz[i]) {
				rez.push_back(i);
				rez.push_back(viz[i]);
			}
		unic (rez);
	}
	for (int i = 0; i < nr/2; ++i) {
		if (el[i].size() < 2) {
			el[i].push_back(x);
			solve(x+1);
			el[i].pop_back();
		}
	}
}

int main() {
	solve (0);

	cout << final.size() << "\n";
//	FORIT(it,final) {
//		cout << "\n";
//		FORIT(it2,*it)
//			cout << *it2 << " ";
//	}
	return 0;
}
