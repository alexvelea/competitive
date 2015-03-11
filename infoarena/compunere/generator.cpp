#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

ifstream in;
ofstream out;

string read(ifstream &fin) {
	string aux, rez;
	while (fin >> aux) {
		rez += aux;
		rez += '#';
	}
	fin.close();
	return rez;
}

void solve(vector<int> &a) {
	random_shuffle(a.begin(), a.end());	
}

int main() {
    srand(time(NULL));
 	for (int t = 0; t < 2000; ++t) {
//		int n = rand() % 4000 + 100, m = rand() % 4000 + 100;
		int n = 10;
		int m = 20;

		vector<int> a(n), b(m);
		
		for (int i = 0; i < n; ++i) {
			a[i] = i;
		}

		for (int j = 0; j < m; ++j) {
			b[j] = j;
		}

		solve(a);
		solve(b);

		out.open("compunere.in");
		out << n << ' ' << m << '\n';
		for (auto itr : a) {
			out << itr << ' ';
		}
		for (auto itr : b) {
			out << itr << ' ';
		}
		out.close();

 		system("./compunere");
		in.open("compunere.in");
		string x = read(in);

  		system("./brut");
		in.open("compunere.in");
		string y = read(in);   	

		if (t % 10 == 0) {
			cerr << t << '\n';
		}

		if (x != y) {
			cerr << "Error\n";
		}
	}


	return 0;
}
