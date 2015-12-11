#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

ifstream in("pamant.in");
ofstream out("pamant.out");

vector<int> vertex[kMaxN], rezA, rezB;
bool bad[kMaxN], viz[kMaxN];
int deep[kMaxN], dp_deep[kMaxN], d, father[kMaxN];

void biconex(int nod) {
	viz[nod] = true;
	deep[nod] = ++d;
	dp_deep[nod] = d;
	int nr = 0;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (viz[oth]) {
            dp_deep[nod] = min(dp_deep[nod], deep[oth]);
		} else {
			father[oth] = nod;
			biconex(oth);
			dp_deep[nod] = min(dp_deep[nod], dp_deep[oth]);
			if (dp_deep[oth] == deep[nod]) {
				bad[nod] = true;
			}
			nr++;
		}
	}
	if (father[nod] == 0 and nr <= 1)
		bad[nod] = false;
	if (father[nod] == 0 and nr > 1)
		bad[nod] = true;
}


int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			rezA.push_back(i);
            biconex(i);
		}
	
    for (int i = 1; i <= n; ++i)
		if (bad[i])
			rezB.push_back(i);

    out << rezA.size() << '\n';
	for (int i = 0; i < int(rezA.size()); ++i)
		out << rezA[i] << ' ';
	out << '\n';

	out << rezB.size() << '\n';
	for (int i = 0; i < int(rezB.size()); ++i)
		out << rezB[i] << ' ';
	out << '\n';
	in.close();
	out.close();
	return 0;
}
