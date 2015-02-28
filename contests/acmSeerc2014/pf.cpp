#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

const int kMaxN = 61005, Buffer = 250;

ifstream in("input.txt");
ofstream out("output.txt");

unordered_map<int, int> elements[kMaxN / Buffer];
vector<int> Rez;
int el[kMaxN], all[kMaxN / Buffer];

int n, rez, under;

void up_rez() {
	rez++;
	for (int i = 0; i * Buffer <= n; ++i)
		under += elements[i][rez - all[i]];
}

void update(int ind) {
	if (el[ind] + all[ind / Buffer] <= rez)
		--under;
	elements[ind / Buffer][el[ind]]--;
	el[ind]++;
	if (el[ind] + all[ind / Buffer] <= rez)
		++under;
	elements[ind / Buffer][el[ind]]++;
}

int main() {
	time_t T = clock();
	while (1) {
		int k;
		in >> n >> k;
		if (n == 0)
			break;

		vector<int> e;

        for (int i = 0; i * Buffer <= n; ++i) {
			elements[i].erase(elements[i].begin(), elements[i].end());
			all[i] = 0;
		}
		
        e.clear();
		for (int i = 1; i <= n; ++i) {
			in >> el[i];
			e.push_back(el[i]);
			elements[i / Buffer][el[i]]++;
		}
		sort(e.begin(), e.end());

		rez = e[n / 2];
		under = 0;
		for (int i = 1; i <= n; ++i)
			if (el[i] <= rez)
				++under;

		for (int K = 1; K <= k; ++K) {
			int st, dr;
			in >> st >> dr;
			for (int i = 0; i * Buffer <= n; ++i) {
				int c1 = i * Buffer, c2 = (i + 1) * Buffer - 1;
				int x = max(c1, st), y = min(dr, c2);
				if (c1 == x and c2 == y) {
					// complet
 					under -= elements[i][rez - all[i]];
					all[i]++;
				} else {
					if (x <= y) {
						while (x <= y) {
							update(x);
							++x;
						}
					}
				}
			}
			while (under < (n + 1) / 2) {
				up_rez();
			}
			Rez.push_back(rez);
		}
	}
	for (int itr : Rez)
		out << itr << '\n';
	cerr << 1.0 * (clock() - T) / CLOCKS_PER_SEC << '\n';
	in.close();
	out.close();
	return 0;
}

