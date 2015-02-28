#include <fstream>
using namespace std;

ifstream in("semne3.in");
ofstream out("semne3.out");

int n, rez[500000];

int main() {
	string txt;
	int aux;
	in >> aux;
	in >> txt;
	txt += '<';
	for (int st = 0; st < txt.size();) {
		int a = st;
		while (st < txt.size() and txt[st] == '>')
			++st;
		for (int b = st; b >= a; --b)
			rez[b] = ++n;
		++st;
	}
	for (int i = 0; i < txt.size(); ++i)
		out << rez[i] << ' ';
	return 0;
}
