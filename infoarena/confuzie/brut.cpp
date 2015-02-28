#include <fstream>
#include <vector>
using namespace std;

ifstream in("confuzie.in");
ofstream out("confuzie2.out");

int father[200005];
int viz[200005];
int black[200005];

int n, q;
vector<int> vertex[200005];


void df(int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) 
		if (not viz[vertex[nod][i]]) {
			father[vertex[nod][i]] = nod;
			df(vertex[nod][i]);
		}
	return ;
}

int main() {
	in >> n >> q;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
	}
	df(1);
	while (q--) {
		int t;
		in >> t;
		if (t == 0) {
			int x;
			in >> x;
			black[x] ^= 1;
		} else {
			int x, y;
			in >> x >> y;
			int rez = -1;
			x = father[x];
			while (y != x) {
				if (black[y])
					rez = y;
				y = father[y];
			}
			out << rez << '\n';
		}
	}
	out.close();
	return 0;
}
