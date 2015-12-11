#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("pamant.in");
ofstream out("pamant2.out");

const int kMaxN = 100005;
vector<int> vertex[kMaxN], rezA, rezB;

bool viz[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (not viz[oth])
			df(oth);
	}
	return ;
}

int n, m;

int make_df() {
	int rez = 0;
	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			df(i);
			++rez;
		}
	return rez;
}

void make_z() {
	for (int i = 1; i <= n; ++i)
		viz[i] = false;
}

int main() {
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
 		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			rezA.push_back(i);
			df(i);
		}
	make_z();
	int d = make_df();
	make_z();
	for (int i = 1; i <= n; ++i) {
		viz[i] = true;
 		int x = make_df();
		make_z();

		if (vertex[i].size() == 0)
			continue;

		if (x != d)
			rezB.push_back(i);
	}
    out << rezA.size() << '\n';
	for (int i = 0; i < int(rezA.size()); ++i)
		out << rezA[i] << ' ';
	out << '\n' << rezB.size() << '\n';
	for (int i = 0; i < int(rezB.size()); ++i)
		out << rezB[i] << ' ';
	out << '\n';
	in.close();
	out.close();
	return 0;
}
