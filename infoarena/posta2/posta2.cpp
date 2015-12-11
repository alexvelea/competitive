#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("posta2.in");
ofstream out("posta2.out");

const int kMaxN = 100005;

vector<pair<int, int> > vertex[kMaxN];
bool good[kMaxN], imp[kMaxN];

int remaining[kMaxN], cost[kMaxN];

void df(int nod) {
	good[nod] = false;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i].first;
		
		--remaining[oth];
		if (remaining[oth] <= 1 and (not imp[oth]) and (good[oth]))
			df(oth);
	}
}

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i < n; ++i) {
   		int a, b, c;
		in >> a >> b >> c;
		vertex[a].push_back(make_pair(b, c));
		vertex[b].push_back(make_pair(a, c));
	} 	
	
	for (int i = 1; i <= n; ++i)
		in >> cost[i];
	
    for (int i = 1; i <= m; ++i) {
		int x;
		in >> x;
		imp[x] = true;
	}

	for (int i = 1; i <= n; ++i) {
		good[i] = true;
		remaining[i] = vertex[i].size();
	}

	for (int i = 1; i <= n; ++i)
		if (remaining[i] <= 1 and imp[i] == false)
			df(i);

	int64 rez = 0, mx = 0;
	for (int i = 1; i <= n; ++i)
		if (good[i]) {
			rez += (remaining[i] - 1) * cost[i];
			for (int itr = 0; itr < int(vertex[i].size()); ++itr) {
            	int oth = vertex[i][itr].first;
				int c = vertex[i][itr].second;
 				if (good[oth])
					rez += c;
			}
			if (mx < 1LL * (remaining[i] - 1) * cost[i])
				mx = 1LL * (remaining[i] - 1) * cost[i];
		}

	rez -= mx;
	out << rez << '\n';

	in.close();
	out.close();
	return 0;
}

