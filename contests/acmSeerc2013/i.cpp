#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 5055;

vector<int> vertex[kMaxN], ord;
bool viz[kMaxN];

int edge[kMaxN / 30][kMaxN], q[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int act = vertex[nod][i];
		if (not viz[act])
			df(act);
	}
	ord.push_back(nod);
}

int sum(int a) {
	int rez = 0;
	while (a) {
		rez ++;
		a -= a & (-a);
	}
	return rez;
}

void make_empty() {
	for (int i = 0; i < kMaxN; ++i) {
		vertex[i].clear();
		viz[i] = false;
		q[i] = 0;
	}
	ord.clear();
	for (int i = 0; i < kMaxN / 30; ++i)
		for (int j = 0; j < kMaxN; ++j)
			edge[i][j] = 0;
}

int main() {
	int n, k;
	while (cin >> n) {
		cin >> k;
        
	 	for (int i = 1; i <= k; ++i)
			cin >> q[i];
		for (int i = 1; i <= n; ++i) {
			int act, oth;
	 		cin >> act;
			char c;
			c = cin.get();
            while (c != '\n') {
                cin >> oth;
                vertex[act].push_back(oth);
                c = cin.get();
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (not viz[i])
                df(i);
        }
        for (int i = 1; i <= n; ++i)
            edge[i / 30][i] |= (1 << (i % 30));
        for (int i = 0; i < n; ++i) {
            int nod = ord[i];
            for (int it = 0; it < int(vertex[nod].size()); ++it)
                for (int p = 0; p <= n / 30; ++p)
                    edge[p][nod] |= edge[p][vertex[nod][it]];
        }
        int mx = 0;
        int poz = 0;
        for (int i = 1; i <= k; ++i) {
            int nod = q[i];
            int rez = 0;
            for (int p = 0; p <= n / 30; ++p)
                rez += sum(edge[p][nod]);
            if (rez > mx || (rez == mx && poz > i)) {
                mx = rez;
                poz = nod;
            }           
        }
        cout << poz << '\n';
		make_empty();
    }
	return 0;
}
