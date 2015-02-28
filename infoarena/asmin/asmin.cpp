#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 16005;
ifstream in("asmin.in");
ofstream out("asmin.out");

int n, k;
int R[max_n], V[max_n], father[max_n];
bool viz[max_n];
vector<int> edge[max_n], sol;
long long sum, rez;

void df (int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(edge[nod].size()); ++i)
		if (not viz[edge[nod][i]]) {
			father[edge[nod][i]] = nod;
			df (edge[nod][i]);
		}
	V[nod] = R[nod] - R[father[nod]];
	V[nod] += k;
	V[nod] %= k;
}

void solve (int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(edge[nod].size()); ++i)
		if (not viz[edge[nod][i]]) {
			long long act = sum;
			int a, b;
			int other = edge[nod][i];

			a = V[nod];
			b = V[other];
			act -= V[nod];
			act -= V[other];
			V[other] = R[other];
			V[nod] = R[nod] - R[other];
			V[nod] += k;
			V[nod] %= k;
			act += V[other];
			act += V[nod];
			if (act < rez) {
				rez = act;
				sol.clear();
			}	
			if (act == rez)
				sol.push_back (other);
			int last_sum = sum;
			sum = act;
			solve (other);

			sum = last_sum;
			V[nod] = a;
			V[other] = b;
		}
}

int main() {
	in >> n >> k;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i)
		in >> R[i];
	df(1);
 	for (int i = 1; i <= n; ++i) {
		viz[i] = 0;
		sum += V[i];
	}
	rez = sum;
	sol.push_back(1);
 	solve (1);
	out << rez << ' ' << sol.size() << '\n';
	sort(sol.begin(), sol.end());
	for (int i = 0; i < int(sol.size()); ++i)
		out << sol[i] << ' ';
	return 0;
}
