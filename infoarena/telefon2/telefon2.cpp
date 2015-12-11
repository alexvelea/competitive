//Problem telefon2 from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("telefon2.in");
ofstream out("telefon2.out");

int n;
int fth[kMaxN];
bool End[kMaxN], viz[kMaxN];
vector<pair<int, int> > Rez;

int df(int nod) {
	viz[nod] = true;
	if (viz[fth[nod]])
		return nod;
	return df(fth[nod]);
}

int main() {
 	in >> n;
	for (int i = 1; i <= n; ++i)
		End[i] = true;
	for (int i = 1; i <= n; ++i) {
		in >> fth[i];
		End[fth[i]] = false;
	}

	int rez = 0;

    for (int i = 1; i <= n; ++i) {
		if (End[i] == true) {
			++rez;
			int nod = df(i);
 			Rez.push_back(make_pair(i, nod));   		
		}
	}

    int a = rez;
	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			++rez;
			int nod = df(i);
			Rez.push_back(make_pair(i, nod));
		}

	Rez.push_back(Rez.front());
	if (a == 0 and rez == 1)
		out << 0 << '\n';
	else {
		out << rez << '\n';
		for (int i = 0; i < rez; ++i)
			out << Rez[i].second << ' ' << Rez[i + 1].first << '\n';
	}
	return 0;
}
