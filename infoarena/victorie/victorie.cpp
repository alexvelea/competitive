#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("victorie.in");
ofstream out("victorie.out");

const int kMaxN = 100005;

vector<vector<int> > rez;
vector<int> vertex[kMaxN];

int deep[kMaxN], low[kMaxN];
stack<int> biconex_st;

bool good[kMaxN], goodB[3 * kMaxN];

void new_cb(int nod) {
    vector<int> r;
    while (1) {
		if (good[biconex_st.top()])
			goodB[rez.size()] = true;
//		cerr << biconex_st.top() << "<----\t" << good[biconex_st.top()] << '\n';
        r.push_back(biconex_st.top());
        if (biconex_st.top() == nod)
            break;
        biconex_st.pop();
    }
    biconex_st.pop();
    
    rez.push_back(r);
}

void biconex(int nod, int parent, int d) {
    deep[nod] = low[nod] = d;
    biconex_st.push(nod);
    for (auto itr : vertex[nod]) {
        if (itr == parent)
            continue;
        if (not deep[itr]) {
            biconex(itr, nod, d + 1);
            if (low[itr] >= deep[nod]) {
                new_cb(itr);
                rez.back().push_back(nod);
            }
            low[nod] = min(low[nod], low[itr]);
        } else {
            low[nod] = min(low[nod], deep[itr]);
			if (deep[nod] > deep[itr] and deep[itr] % 2 == deep[nod] % 2) {
// 				cerr << "PENIS!\n";   			
//	 			cerr << nod << '\t' << itr << '\n';   			
				good[nod] = true;
			}
        }
    }
}

int main() {
    int n, m;
    in >> n >> m;
    while (m--) {
        int a, b;
        in >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
		if (not deep[i]) {
			biconex(i, 0, 1);
		}
	}
//	for (int i = 1; i <= n; ++i) {
//		cerr << good[i] << '\t';
//	}
//	cerr << "\n";
    
    vector<int> Rez;
/*	for (auto itr : rez) {
		cerr << '\n';
		for (auto itr2 : itr) {
			cerr << itr2 << '\t';
		}
	}*/


	for (int i = 0; i < int(rez.size()); ++i) {
		if (goodB[i]) {
			for (int j = 0; j < int(rez[i].size()); ++j) {
				Rez.push_back(rez[i][j]);
			}
		}
	}

	sort(Rez.begin(), Rez.end());
	rez.resize(unique(Rez.begin(), Rez.end()) - Rez.begin());
	
	out << Rez.size() << '\n';
	for (auto itr : Rez) {
		out << itr << ' ';
	}
    return 0;
}
