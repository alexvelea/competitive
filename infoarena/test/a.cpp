#include <fstream>
#include <vector>
using namespace std;

ifstream in("date.in");
ofstream out("date.out");

vector<int> rez;

int main() {
	int n, sum = 0;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		in >> x;
		sum += x;
//		out << sum << ' ';
		rez.push_back(sum);
	}
	for (int i = 0; i < int(rez.size()); ++i)
		out << rez[i] << ' '; 
	in.close();
	out.close();
	return 0;
}
