#include <iostream>                 
#include <vector>
using namespace std;

const int kMaxN = 1000005;

int down[kMaxN], deq[kMaxN];
vector<pair<int, int> > vertex[kMaxN];

int St[kMaxN], Dr[kMaxN], Mid[kMaxN];
int rez[kMaxN];

int solve(int st, int dr) {
	if (st > dr)
		return 0;

	int nod = st;

	int mx = nod;
	for (auto itr : vertex[st]) {
		if (itr.second == 0)
			mx = max(mx, itr.first);
		dr = max(dr, itr.first);
	}
	if (mx == nod) 
		;
	else {
		mx = max(solve(st + 1, mx), mx);
	}
	dr = max(dr, mx);
 	rez[++rez[0]] = nod;
	dr = max(dr, solve(mx + 1, dr));
	
 	St[nod] = st;
 	Mid[nod] = mx;   
	Dr[nod] = dr;   
	return dr;
}

int main() {
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	bool ok = true;
	while (k--) {
		int a, b;
		string str;
		cin >> a >> b >> str;
		if (a >= b)
			ok = false;
		if (str == "LEFT") {
			vertex[a].emplace_back(b, 0);
		} else {
			vertex[a].emplace_back(b, 1);
		}
	}

/*	for (int i = n, dr = 0; i; --i) {
		int mx = i;
		for (auto itr : vertex[i])
			mx = max(itr.first, mx);
		while (dr and mx >= deq[dr]) {
			mx = max(mx, down[deq[dr]]);
			--dr;
		}
		down[i] = mx;
		deq[++dr] = i;
	}*/

//	for (int i = 1; i <= n; ++i)
//		cerr << i << '\t' << down[i] << '\n';

 	solve(1, n);
	for (int i = 1; i <= n; ++i) {
//		cerr << i << '\t' << St[i] << '\t' << Mid[i] << '\t' << Dr[i] << '\n';
		for (auto itr : vertex[i]) {
			if (itr.second == 0) {
				if (St[i] <= itr.first and itr.first <= Mid[i])
					;
				else
					ok = false;
			} else {
				if (Mid[i] < itr.first and itr.first <= Dr[i])
					;
				else 
					ok = false;
			}
		}
	}
	
	if (ok) {
		for (int i = 1; i <= n; ++i)
			cout << rez[i] << ' ';
	} else {
		cout << "IMPOSSIBLE\n";
	}
	return 0;
}
