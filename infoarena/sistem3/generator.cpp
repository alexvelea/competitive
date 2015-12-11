#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

int p[kMaxN], rez[kMaxN], val[kMaxN];
vector<int> nxt, vertex;

int main() {
	int n = 10000;
	int Mod = 30011;
	srand(time(NULL));
	for (int i = 1; i <= 50; ++i){
		ofstream out("sistem3.in");
 		vertex.clear();
		nxt.clear();
		for (int i = 1; i <= n; ++i)
			nxt.push_back(i);
		int ind = rand() % (n - 5) + 1;
		for (int i = 0; i < ind; ++i) {
			vertex.push_back(nxt[i]);
			p[nxt[i]] = nxt[(i + 1) % ind];
		}
		random_shuffle(nxt.begin(), nxt.end());
		for (int i = ind; i < n; ++i) {
			int nod = nxt.back();
			nxt.pop_back();
			int ind = rand() % vertex.size();
			p[nod] = vertex[ind];
			vertex.push_back(nod);
		}
 		for (int i = 1; i <= n; ++i) {
			rez[i] = rand() % Mod;
			val[i] = 0;
		}
		out << n << ' ' << Mod << '\n';
		for (int i = 1; i <= n; ++i) {
			int a = i;
			int b = p[a];
			int c = rand() % (Mod - 1) + 1;
 			val[a] += (1LL * (Mod + rez[a] - rez[b]) * c) % Mod;
			val[b] += (1LL * (Mod + rez[b] - rez[a]) * c) % Mod;
			val[a] %= Mod;
			val[b] %= Mod;
			out << a << ' ' << b << ' ' << c << '\n';
		}
		for (int i = 1; i <= n; ++i)
			out << val[i] << ' ';
		out.close();
		ofstream out2("sistem3.out");
		for (int i = 1; i <= n; ++i)
			out2 << rez[i] << '\n';
		out2.close();
		system("./check");
	}
	return 0;
}

