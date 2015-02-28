#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 100005;

int n, m;
int father[kMaxN], color[kMaxN], under[kMaxN];
int rez[kMaxN];
vector<int> edge[kMaxN], colors;
map<int, int> num;

vector<pair<int, int> > query[kMaxN];



bool viz[kMaxN];


int aib[kMaxN];
int aib_query(int val) {
	int rez = 0;
	while (val) {
		rez += aib[val];
		val -= val & (-val);
	}
	return rez;
}

void aib_update(int poz, int val) {
	if (poz == 0)
		return ;
	while (poz <= n) {
		aib[poz] += val;
		poz += poz & (-poz);
	}
	return ;
}

void make_father(int nod) {
	for (int i = 0; i < edge[nod].size(); ++i) {
		int oth = edge[nod][i];
		if (father[oth])
			continue;
		father[oth] = nod;
		make_father(oth);
		under[nod] += under[oth];
	}
	under[nod]++;
}

void put_inside(int nod) {
	colors.push_back(color[nod]);
	for (int i = 0; i < int(edge[nod].size()); ++i) {
		int oth = edge[nod][i];
		if (father[oth] == nod)
			put_inside(oth);
	}

}

void solve(int nod) {
	int mx = 0;
 	int down = -1;
	viz[nod] = true;
	for (int i = 0; i < int(edge[nod].size()); ++i) {
		int oth = edge[nod][i];
		if (father[oth] == nod) 
			if (mx < under[oth]) {
				mx = under[oth];
				down = oth;
			}
	}
	if (down != -1)
		solve(down);
	colors.clear();
	if (down != -1) {
		for (int i = 0; i < int(edge[nod].size()); ++i) {
			int oth = edge[nod][i];
			if (father[oth] == nod and oth != down)
				put_inside(oth);
		}
	}
	colors.push_back(color[nod]);
	sort(colors.begin(), colors.end());
	int m = colors.size();
//	cerr << "\t#" << nod << '\n';
	for (int i = 0; i < m;) {
		int st = i, dr = i;
		while (dr < m and colors[st] == colors[dr])
			++dr;
//		cerr << colors[st] << '\t' << dr - st << '\n';
		i = dr;
		aib_update(num[colors[st]], -1);
		num[colors[st]] += (dr - st);
		aib_update(num[colors[st]], +1);
	}
    for (int i = 0; i < int(query[nod].size()); ++i) {
		int val = query[nod][i].first;
		int ind = query[nod][i].second;
		val --;
		if (val >= n)
			val = n;
		rez[ind] = aib_query(n) - aib_query(val);
	}
	return ;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> color[i];
	}
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	father[1] = 1;
	make_father(1);
	for (int i = 1; i <= m; ++i) {
		int v, k;
		cin >> v >> k;
		query[v].push_back(make_pair(k, i));
	}
	for (int i = 1; i <= n; ++i)
		if (viz[i] == 0) {
	   		int nod = i;
			while (nod != 1 and viz[father[nod]] == false)
				nod = father[nod];
			solve(nod);
			for (map<int, int> :: iterator it = num.begin(); it != num.end(); ++it) {
				aib_update(it->second, -1);
			}
			num.clear();
		}
	for (int i = 1; i <= m; ++i)
		cout << rez[i] << '\n';
	return 0;
}
