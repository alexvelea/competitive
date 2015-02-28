#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int max_n = 300;
ifstream in("soc.in");
ofstream out("soc.out");

vector<int> v;
vector<vector<int> > comp[max_n];
int st_size = -1;

bool viz[max_n];

int n;
bool vertex[max_n][max_n];
int score[max_n];

void df(int nod, int x, vector<int> &target) {
	for (int i = 1; i <= max_n; ++i)
		if (vertex[nod][i] == x ^ 1 && not viz[i]) {
			target.push_back(i);
			viz[i] = true;
			df(i, x, target);
		}
}

struct rez {
	int nr;
	vector<int> el;
	rez() {
		nr = 0;
		el.clear();
	}
	rez(int _nr, int _el) {
		nr = _nr;
		el.clear();
		el.push_back(_el);
	}
	void max(rez oth) {
		if (nr < oth.nr) {
	   		*this = oth;
		}
	}
	void join(rez oth) {
		nr += oth.nr;
		for (int i = 0; i < int(oth.el.size()); ++i)
			el.push_back(oth.el[i]);
	}
	void show() {
		out << nr << '\n';
		out << el.size() << '\n';
		for (int i = 0; i < int(el.size()); ++i)
			out << el[i] << ' ';
		out << '\n';
		return ;
	}
};

rez clica(vector<int> c);

rez independent(vector<int> c) {
	if (int(c.size()) == 1)
		return rez(score[c[0]], c[0]);
    
	++st_size;
	for (int i = 1; i <= n; ++i)
		viz[i] = true;
	for (int i = 0; i < int(c.size()); ++i)
		viz[c[i]] = false;
	for (int i = 0; i < int(c.size()); ++i)
        if (not viz[c[i]]) {
			comp[st_size].push_back(v);
			comp[st_size][comp[st_size].size() - 1].push_back(c[i]);
			viz[c[i]] = true;
			df(c[i], 1, comp[st_size][int(comp[st_size].size()) - 1]);
		}
	rez f;
	for (int i = 0; i < int(comp[st_size].size()); ++i)
		f.join(clica(comp[st_size][i]));
	--st_size;
	return f;
}

rez clica(vector<int> c) {
	if (int(c.size()) == 1)
		return rez(score[c[0]], c[0]);
   
	++st_size;
	for (int i = 1; i <= n; ++i)
		viz[i] = true;
	for (int i = 0; i < int(c.size()); ++i)
		viz[c[i]] = false;
	for (int i = 0; i < int(c.size()); ++i)
		if (!viz[c[i]]) {
			comp[st_size].push_back(v);

			viz[c[i]] = true;
			df(c[i], 0, comp[st_size][int(comp[st_size].size()) - 1]);
		}
	rez mx;
	for (int i = 0; i < int(comp[st_size].size()); ++i)
		mx.max(independent(comp[st_size][i]));
	--st_size;
	return mx;
}

int main() {
	int m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		in >> score[i];
	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a][b] = vertex[b][a] = true;
	}
	vector<int> a;
	for (int i = 1; i <= n; ++i)
		a.push_back(i);
	clica(a).show();
	return 0;
}
