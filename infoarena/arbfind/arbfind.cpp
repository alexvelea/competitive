//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("arbfind.in");
ofstream out("arbfind.out");

const int kMaxN = 70005;

int Z[kMaxN], Rez[kMaxN];
vector<int> vertex[kMaxN], vertex2[kMaxN];

int who[kMaxN], ind = 0;
int finalRez[kMaxN];
int Sp[kMaxN];

void df(int nod, vector<int> vertex[], string &txt) {
 	txt += 'd';
	who[++ind] = nod;
	for (int itr : vertex[nod]) {
		df(itr, vertex, txt);
	}
	txt += 'u';
	return ;
}

void z(string &a, string &b) {
	int mx = 0, ind = 0;
	Z[0] = a.size();
	for (int i = 1; i < int(a.size()); ++i) {
		if (mx >= i) {
			Z[i] = min(Z[i - ind], mx - i);
		}
		while (a[i + Z[i]] == a[Z[i]] and i + Z[i] < int(a.size()))
			++Z[i];
		if (i + Z[i] > mx) {
			mx = i + Z[i];
			ind = i;
		}
	}
 	
	mx = ind = 0;
	for (int i = 0; i < int(b.size()); ++i) {
		if (mx > i)
			Rez[i] = min(Z[i - ind], mx - i);
		while (a[Rez[i]] == b[i + Rez[i]] and i + Rez[i] < int(b.size()) and Rez[i] < int(a.size()))
			++Rez[i];
		if (Rez[i] + i > mx) {
			mx = Rez[i] + i;
			ind = i;
		}
	}
}

int main() {
	int n, m;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int el;
    	in >> el;
		while (el--) {
			int x;
			in >> x;
			vertex[i].push_back(x);
		}
	}

	in >> m;
	for (int i = 1; i <= m; ++i) {
		int el;
    	in >> el;
		while (el--) {
			int x;
			in >> x;
			vertex2[i].push_back(x);
		}
	}

	string a, b;
	df(1, vertex, a);
	ind = 0;
	df(1, vertex2, b);
	z(a, b);
	Sp[0] = 1;
	for (int i = 1; i < int(b.size()); ++i)
		Sp[i] = Sp[i - 1] + (b[i] == 'd');

	ind = 0;

	for (int i = 0; i < int(b.size()); ++i)
		if (b[i] == 'd') {
			if (i == 0)
				finalRez[who[++ind]] = Sp[Rez[i] - 1];
			else
				finalRez[who[++ind]] = Sp[i + Rez[i] - 1] - Sp[i - 1];
		}

	for (int i = 1; i <= m; ++i)
		out << finalRez[i] << '\n';
    return 0;
}
