#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
vector<int> S;
int main() {
	ofstream out("tram.in");
	int n = 999;
	int m = 5000;
	out << n << ' ' << m << '\n';
	int x = 5;
 	for (int i = 1; i <= m; ++i) {
		if (i == 1000)
			x--;
		if (i == 2000)
 			x--;
		if (i == 3000)
			x--;
		if (i % x == 0 || S.size() == 2 * n) {
			int ind = rand() % S.size();
			out << "L " << S[ind];
			S[ind] = S[S.size() - 1];
			S.pop_back();
		} else {
			out << "E";
			S.push_back(i);
		}
		out << '\n';
	}
}
