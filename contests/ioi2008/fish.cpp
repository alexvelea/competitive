#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int max_f = 500005, max_k = 500005;
ifstream in("fsh19d.in");
ofstream out("fish.out");

pair<int, int> max_fish[max_k], fish[max_f];
vector<int> where[max_k];

int aint[8 * max_k];
int F, K, MOD;
int ap[max_k], id[max_k];

void update (int st, int dr, int nod, int where, int val) {
	if (st == dr) {
		aint[nod] = val;
		return ;
	}
	int m = (st + dr) / 2;
	if (where <= m)
		update (st, m, 2 * nod, where, val);
	else
		update (m + 1, dr, 2 * nod + 1, where, val);
	aint[nod] = (aint[2 * nod] * aint[2 * nod + 1]) % MOD;
	return ;
}

int query (int c1, int c2, int st, int dr, int nod) {
	if (c1 > c2)
		return 1;
	if (st <= c1 && c2 <= dr)
		return aint[nod];
	if (c2 < st || dr < c1)
		return 1;
	int m = (c1 + c2) / 2;
	return (query(c1, m, st, dr, 2 * nod) * query(m + 1, c2, st, dr, 2 * nod + 1) ) % MOD;
}

void get_max (int &a, int b) {
	if (a < b)
		a = b;
}

int binary (int val) {
	int p = 1, rez = 0;
	while (p <= K)
		p <<= 1;
	while (p) {
		if (rez + p <= K)
			if (max_fish[rez + p].first < val)
				rez += p;
		p >>= 1;
	}
	return rez;
}


int main() {
	for (int i = 0; i < 8 * max_k; ++i)
		aint[i] = 1;
	in >> F >> K >> MOD;
	for (int i = 1; i <= F; ++i) 
		in >> fish[i].first >> fish[i].second;
	for (int i = 1; i <= K; ++i)
		max_fish[i].second = i;
	for (int i = 1; i <= F; ++i)
		get_max(max_fish[fish[i].second].first, fish[i].first);
	
	sort (max_fish + 1, max_fish + 1 + K);
	sort (fish + 1, fish + F + 1);
	
	for (int i = 1; i <= F; ++i)
		where[fish[i].second].push_back(fish[i].first);
	int it = 1;
	int rez = 0;
	for (int i = 1; i <= K; ++i)
		id[max_fish[i].second] = i;
 	for (int i = 1; i <= K; ++i) {
//		cerr << max_fish[i].first << "#" << max_fish[i].second << '\n';
		// inseram in aint
		int l = max_fish[i].first;
		while (it <= F && fish[it].first * 2 <= l) {
			ap[fish[it].second]++;
			update(1, K, 1, id[fish[it].second], ap[fish[it].second] + 1);
			++it;
		}
		int st = 0, gem = max_fish[i].second;
 		while (where[gem][st] * 2 <= l)
			++st;
 		int c1 = binary(2 * where[gem][st]);
//		cerr << rez << "!!!!\t " << i << '\n';
 		rez += (query(1, K, 1, i - 1, 1) * query(1, K, i + 1, c1, 1)) % MOD;
		rez += (query(1, K, 1, i - 1, 1) * st) % MOD;
		while (rez >= MOD)
			rez -= MOD;
	}
	out << rez << '\n';
	return 0;
}
