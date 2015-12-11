//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define int64 long long

ifstream in("strmatch.in");
ofstream out("strmatch.out");

const int kMaxN = 2000005;

vector<int> r;

char a[kMaxN], b[kMaxN];
int Z[kMaxN];

void solve() {
	// facem z pe sirul b
	Z[0] = b.size();
	int mx = 0, ind = 0;
	for (int i = 1; i < int(b.size()); ++i) {
		Z[i] = 0;

		if (mx > i) {
			Z[i] = min(Z[i - ind], mx - i);
			Z[i] = min(Z[i], int(b.size()) - i);
		}
		
		while (b[Z[i]] == b[Z[i] + i] and Z[i] + i < int(b.size()))
			++Z[i];
		
		if (i + Z[i] > mx) {
			ind = i;
			mx = i + Z[i];
		}
	}
	
    mx = ind = 0;
	for (int i = 0; i < int(a.size()); ++i) {
		int rez = 0;

		if (mx > i) {
			rez = min(Z[i - ind], mx - i);
			rez = min(rez, int(a.size()) - i);
		}
		
		while (b[rez] == a[rez + i] and rez < int(b.size()) and i + rez < int(a.size()))
			++rez;
		
		if (i + rez > mx) {
			ind = i;
			mx = i + rez;
		}
		if (rez == int(b.size()))
			r.push_back(i);
	}
}

int main() {
	in >> a >> b;
	in.close();

	solve();
    
	out << r.size() << '\n';
	for (int i = 0; i < min(1000, int(r.size())); ++i)
		out << r[i] << ' ';
	return 0;
}
