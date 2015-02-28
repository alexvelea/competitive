#include <fstream>
using namespace std;

int el[20005], viz[20005];
ifstream in("perm2.in");
ofstream out("perm2.out");

int solve(int x) {
	if (viz[x] == 1)
		return 0;
	viz[x] = 1;
	return 1 + solve(el[x]);
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	int rez = 1;
	for (int i = 1; i <= n; ++i)
		if (viz[i] == 0) {
			int x = solve(i);
			rez = rez * x / gcd(rez, x);
		}
	out << rez << '\n';
	return 0;
}

