#include <fstream>
#include <iostream>
using namespace std;

ifstream in("kami.in");
ofstream out("kami2.out");


const int kMaxN = 100005;
int init[kMaxN];

int main() {
	int n, m;
	in >> n;
 	for (int i = 1; i <= n; ++i) {
		in >> init[i];
	}
	in >> m;
	int step = 0;
	for (int i = 1; i <= m; ++i) {
		int t;
		in >> t;
		if (t == 0) {
			int ind, x;
			in >> ind >> x;
			init[ind] = x;
		} else {
			++step;
        	int rez;
			in >> rez;
			long long sum = init[rez];
			rez--;
			while(rez and sum > init[rez]) {
				sum += 1LL * init[rez];
				rez--;
			}
			out << rez << '\n';
		}
	}
}


