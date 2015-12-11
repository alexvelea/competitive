#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int max_n = 16005, INF = 0x3f3f3f3f;
ifstream in("base3.in");
ofstream out("base3.out");

priority_queue<pair<int,int> >pq;
string txt[3];
int n[3];
int g_best[max_n], best[max_n];
bool viz[max_n];

int main() {
	for (int i = 0; i < 3; ++i)
		in >> txt[i];
	for (int i = 0; i < 3; ++i)
		n[i] = txt[i].size();
	for (int i = 1; i <= max_n; ++i)
		g_best[i] = INF;
	for (int st = 0; st < 3; ++st) {
		for (int i = 0; i < max_n; ++i)
			best[i] = INF, viz[i] = false;
		best[0] = 0;
		while (pq.size())
			pq.pop();
		pq.push(make_pair(0, 0));
		while (pq.size()) {
			int nod = pq.top().second;
			pq.pop();
			if (viz[nod])
				continue;
			for (int i = 0; i < 3; ++i) {
				int next_nod = (nod + n[i]) % n[st];
				int next_val = best[nod] + n[i] + n[st] * int((nod + n[i]) / n[st]);
				if (best[next_nod] > next_val) {
					pq.push(make_pair(next_val, next_nod));
					best[next_nod] = next_val;
				}
			}
		}
		for (int i = 0; i < max_n; ++i)
			g_best[i] = min(g_best[i], best[i]);
	}
	int rez = 0;
	for (int i = 0; i < 3; ++i) {
		for (int p = 0; p < n[i]; ++p)
			if (txt[i][p] == '1') {
				int val = abs (p - (n[i] - p - 1));
				cerr << val << '\n';
				val += g_best[val];
				if (rez > val)
					rez = val;
			}
	}
	out << rez << '\n';
	return 0;
}
