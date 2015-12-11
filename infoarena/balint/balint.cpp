#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define int64 long long

ifstream in("balint.in");
ofstream out("balint.out");

const int kMaxN = 100005;

string txt[kMaxN];
vector<pair<char, int> > event[kMaxN];
vector<int> el;

int main() {
	int T;
	in >> T;
    for (int t = 1; t <= T; ++t) {
		int n;
		in >> n;
		for (int i = 1; i <= n; ++i)
			in >> txt[i];
		for (int i = 1; i <= n; ++i) {
			event[i].clear();
			for (int st = 0; st < int(txt[i].size()); ) {
            	int dr = st;
				while (dr < int(txt[i].size()) and txt[i][dr] == txt[i][st])
					++dr;
				event[i].push_back(make_pair(txt[i][st], dr - st));
				st = dr;
			}
		}

        int rez = 0;
		bool ok = true;

		for (int i = 2; ok and i <= n; ++i) {
			if (event[i].size() != event[1].size())
				ok = false;
			for (int itr = 0; itr < int(event[1].size()); ++itr)
				if (event[i][itr].first != event[1][itr].first) {
					ok = false;
				}
		}
		if (ok) {
			for (int itr = 0; itr < int(event[1].size()); ++itr) {
				el.clear();
				for (int i = 1; i <= n; ++i)
					el.push_back(event[i][itr].second);
				sort(el.begin(), el.end());
 				int E = el[el.size() / 2];
				for (int i = 0; i < n; ++i)
					rez += abs(E - el[i]);
			}
			out << "Case #" << t << ": " << rez << '\n';
		} else {
			out << "Case #" << t << ": Fegla Won\n";
		}

	}
	return 0;
}
