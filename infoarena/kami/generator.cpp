#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
int main() {
	int n = 100;
	int m = 100;
	int maxVal = 1000000;
	srand(time(NULL));
	while(1){
		ofstream out("kami.in");
		out << n << "\n";
		for (int i = 1; i <= n; ++i)
			out << rand() % maxVal << ' ';
		out << '\n';
		out << m << '\n';
		for (int i = 1; i <= m; ++i) {
			int x = rand() % 10;
			if (x < 3) {
				out << "0 " << rand() % n + 1 << ' ' << rand() % maxVal << '\n';
			} else {
				out << "1 " << rand() % n + 1 << '\n';
			}
		}
		out.close();
		system("./kami");
		system("./brut");
		system("./same");
		cerr << "Ok\n";
	}
}
