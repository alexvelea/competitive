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

ifstream in("potriveala.in");
ofstream out("potriveala.out");

const int kMaxN = 500005;

string a, b, c;
int st[kMaxN], dr[kMaxN], rez[kMaxN];
int Z[kMaxN];

void solve() {
	// facem z pe sirul b
	Z[0] = b.size();
	int mx = 0, ind;
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
		rez[i] = 0;

		if (mx > i) {
			rez[i] = min(Z[i - ind], mx - i);
			rez[i] = min(rez[i], int(a.size()) - i);
		}
		
		while (b[rez[i]] == a[rez[i] + i] and rez[i] < int(b.size()) and i + rez[i] < int(a.size()))
			++rez[i];
		
		if (i + rez[i] > mx) {
			ind = i;
			mx = i + rez[i];
		}
	}
}

int main() {
	in >> a >> b;
	in.close();

	c = b;
	while (b.size() < a.size())
		b += c;
	
	solve();
	for (int i = 1; i <= int(a.size()); ++i)
		dr[i] = rez[i - 1];
	
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	solve();
	for (int i = 0, j = int(a.size()); i < int(a.size()); --j, ++i) 
		st[j] = rez[i];
	
	int mx = 0;
	for (int i = 1; i <= int(a.size()); ++i)
		if (st[i - 1] + dr[i] > mx)
			mx = st[i - 1] + dr[i];
	
	out << mx << '\n';
    return 0;
}
