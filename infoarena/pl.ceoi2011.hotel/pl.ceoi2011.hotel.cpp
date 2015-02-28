//Problem pl.ceoi2011.hotel from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 500005;

ifstream in("input.txt");
ofstream out("output.txt");

struct Room {
	int cost, nrPerson;
	Room() {
		cost = nrPerson = 0;
	}

	bool operator < (const Room &lhr) const {
		if (nrPerson == lhr.nrPerson)
			return cost < lhr.cost;
		return nrPerson < lhr.nrPerson;
	}
} room[kMaxN], query[kMaxN];

priority_queue<int> pq;
vector<int> rez;

int main() {
	int n, m, o;
	in >> n >> m >> o;
	for (int i = 1; i <= n; ++i) {
		in >> room[i].cost >> room[i].nrPerson;
	}

	for (int i = 1; i <= m; ++i) {
		in >> query[i].cost >> query[i].nrPerson;
	}
	in.close();

	sort(room + 1, room + n + 1);
	sort(query + 1, query + m + 1);

	for (int a = 1, b = 1; a <= n; ++a) {
		while (b <= m and query[b].nrPerson <= room[a].nrPerson) {
			pq.push(query[b].cost);
			++b;
		}
 		if (pq.size()) {
			int v = pq.top();
			if (v > room[a].cost) {
				pq.pop();
				rez.push_back(v - room[a].cost);
//				out << room[a].cost << '\t' << room[a].nrPerson << "\t\t" << v << '\n';
			}
		}
	}

	sort(rez.begin(), rez.end());
	reverse(rez.begin(), rez.end());
	int sum = 0;
	for (int itr : rez) {
		out << itr << '\n';
		sum += itr;
	}
	out << sum << "\n\n";
	out.close();
	return 0;
}
