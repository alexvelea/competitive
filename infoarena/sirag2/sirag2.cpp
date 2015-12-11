#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream in("sirag2.in");
ofstream out("sirag2.out");

const int kMaxN = 100005;

string txt;
int nxt[kMaxN];
char last[kMaxN];
int ind[kMaxN];

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, l;
		in >> n >> l;
		in >> txt;
		n = txt.size();
		for (int i = 0; i < l; ++i) {
			last[i] = '*';
			ind[i] = n;
		}
		int L = n % l;
 		for (int i = n - 1; i >= 0; --i) {
//			cerr << i << ' ' << txt[i] << ' ' << last[L] << '\n';
			if (txt[i] == last[L] or last[L] == '*' or txt[i] == '*') {
				if (txt[i] != '*') {
					last[L] = txt[i];
					ind[L] = i;
				}

				if (i + l >= n)
					nxt[i] = n;
				else
					nxt[i] = nxt[i + l];
			} else {
				nxt[i] = ind[L];
				ind[L] = i;
				last[L] = txt[i];
			}

			L--;
			if (L == -1)
				L = l - 1;
		}
		int mx = l, dr = n;
		for (int i = n - 1; i >= 0; --i) {
			dr = min(dr, nxt[i]);
			if (dr - i > mx)
				mx = dr - i;
		}
//		for (int i = 0; i < n; ++i)
//			cerr << nxt[i] << '\t';
//		cerr << "\n\n";
		mx = int(mx / l) * l;
		out << mx << '\n';
	}
	in.close();
	out.close();
}
