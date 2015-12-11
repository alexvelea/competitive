#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("painting.in");
ofstream out("painting.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int color[kMaxN], query[kMaxN], rez[kMaxN];
bool viz[kMaxN];

vector<int> vertex[kMaxN];
stack<int> st;

void df(int nod) {
	if (not st.size() or (query[nod] and query[nod] > st.top())) {
		st.push(query[nod]);
	}
	if (st.size())
		rez[nod] = color[st.top()];
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (not viz[oth])
			df(oth);
	}
	if (st.size() and st.top() == query[nod])
		st.pop();
}

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	for (int i = 1; i <= m; ++i) {
    	int nod, x;
		in >> nod >> x;
		color[i] = x;
		query[nod] = i;
	}
	df(1);
	for (int i = 1; i <= n; ++i) {
		if (not rez[i])
			rez[i] = 1;
		out << rez[i] << ' ';
	}
    return 0;
}
