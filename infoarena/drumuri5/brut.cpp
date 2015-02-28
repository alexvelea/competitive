#include <fstream>
#include <vector>
using namespace std;

ifstream in("drumuri5.in");
ofstream out("drumuri2.out");

const int kMaxN = 150005;

int n, m;
vector<int> vertex[kMaxN], vertex_back[kMaxN];
bool viz[kMaxN], viz_rez[kMaxN];
int rez[kMaxN];

void df(int nod) {
	viz[nod] = viz_rez[nod] = true;
	for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
		int oth = vertex[nod][itr];
		if (not viz[oth])
			df(oth);
	}
}

void df_back(int nod) {
	viz[nod] = viz_rez[nod] = true;
	for (int itr = 0; itr < int(vertex_back[nod].size()); ++itr) {
		int oth = vertex_back[nod][itr];
		if (not viz[oth])
			df_back(oth);
	}
}


bool solve(int nod) {
	for (int i = 1; i <= n; ++i) {
		viz[i] = false;
		viz_rez[i] = false;
	}
	
	df(nod);
 	
	for (int i = 1; i <= n; ++i)
		viz[i] = false;
	
	df_back(nod);

	viz_rez[nod] = true;
	for (int i = 1; i <= n; ++i)
		if (not viz_rez[i])
			return false;
	return true;
}

int main() {
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
    	int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex_back[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i) {
		if (solve(i)) {
			rez[++rez[0]] = i;
		}
	}

	out << rez[0] << '\n';
	for (int i = 1; i <= rez[0]; ++i)
		out << rez[i] << ' ';
	in.close();
	out.close();
	return 0;
}
