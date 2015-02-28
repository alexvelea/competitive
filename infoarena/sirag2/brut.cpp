#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream in("sirag2.in");
ofstream out("sirag22.out");

const int kMaxN = 10005;

int n, l;
char last[kMaxN];
string txt;

int main() {
	int t;
	in >> t;
	while (t--) {
		in >> n >> l;
		in >> txt;
		n = txt.size();
		int rez = 0;
		for (int st = 0; st < n; ++st) {
			for (int i = 0; i < l; ++i)
				last[i] = '*';
			int dr = st, L = 0;
 			for (; dr < n; ++dr) {
				++L;
				if (L == l)
					L = 0;

				if (txt[dr] == '*')
					continue;
				if (last[L] == '*') {
					last[L] = txt[dr];
				} else {
					if (last[L] != txt[dr])
						break;
				}
			} 
			rez = max(rez, dr - st);
		}
		rez = int(rez / l) * l;
		out << rez << '\n';
	}
	in.close();
	out.close();
}
