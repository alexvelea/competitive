#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 105;

ifstream in("minerale.in");
ofstream out("minerale.out");

vector<pair<int, int> > edge[26];

bool one[26][26];
bool ok[kMaxN][kMaxN][26];

void solve(string &txt) {
	int n = txt.size();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 26; ++j)
			if (one[j][txt[i] - 'a'])
				ok[i][i][j] = true;
	
	for (int l = 1; l < n; ++l)
		for (int st = 0; st + l < n; ++st) {
			int dr = st + l;
 			for (int j = 0; j < 26; ++j)
 				for (int mid = st; mid < dr and not ok[st][dr][j]; ++mid)
					for (int itr = 0; itr < int(edge[j].size()); ++itr) {
						int a = edge[j][itr].first;
						int b = edge[j][itr].second;
						if (ok[st][mid][a] and ok[mid + 1][dr][b])
							ok[st][dr][j] = true;
					}
		}
}

int main() {
	int r, m;
	in >> r >> m;
	for (int i = 1; i <= r; ++i) {
		char A, B, C;
		in >> A;
		in >> B;
		if (B >= 'a' and B <= 'z') {
	    	one[A - 'A'][B - 'a'] = true;
		} else {
			in >> C;
 			edge[A - 'A'].push_back(make_pair(B - 'A', C - 'A'));
		}
	}

	for (int i = 1; i <= m; ++i) {
		string txt;
		in >> txt;
		int n = txt.size();
		solve(txt);
    	
		if (ok[0][n - 1]['S' - 'A']) {
        	out << "1\n";
		} else {
			bool k = false;
			for (int j = 0; j < 26; ++j)
				if (ok[0][n - 1][j] == true)
					k = true;
			if (k)
				out << "2\n";
			else
				out << "0\n";
		}
//		for (int l = 0; l < n; ++l, cerr << '\n')
//			for (int j = 0; j < 4; ++j, cerr << '\t')
//			for (int st = 0; st + l < n; ++st)
//					cerr << ok[st][st + l][j];
		for (int a = 0; a < n; ++a)
			for (int b = 0; b < n; ++b)
				for (int j = 0; j < 26; ++j)
					ok[a][b][j] = 0;
	}
}
