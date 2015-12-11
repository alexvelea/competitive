#include <fstream>
using namespace std;
ofstream fout("data.txt");
int main() {
	int n = int(1e7);
	fout << n << '\n';
	for (int i = 1; i <= n; i += 1) {
		fout << rand() << '\n';
	}
	return 0;
}