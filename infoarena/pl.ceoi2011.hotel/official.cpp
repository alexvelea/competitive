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
		return cost < lhr.cost;
	}
} room[kMaxN], query[kMaxN];

vector<int> rez;

bool viz[kMaxN];

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
	reverse(query + 1, query + m + 1);

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j)
			if (room[j].nrPerson >= query[i].nrPerson and not viz[j]) {
				if (room[j].cost < query[i].cost) {
					rez.push_back(query[i].cost - room[j].cost);
					viz[j] = true;
//	 				out << room[j].cost << '\t' << room[j].nrPerson << "\t\t" << query[i].cost << '\n';   				
				}
				break;
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
