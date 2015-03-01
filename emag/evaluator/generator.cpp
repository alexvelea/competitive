#include <ctime>
#include <cmath>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in;
ofstream out;

string readFromStream(ifstream &in) { // trebuie pus &
	string aux, rez;
	while (in >> aux) {
		rez += aux;
		rez += '#'; // fisierul .out 13 37 e diferit de 1 337
	}
	in.close();
	return rez;
}

int main() {
	srand(time(NULL)); // garanteaza ca genereaza numere random diferite, 
		//altfel o sa genereze aceleasi numere la fiecare rulare
	
	for (int t = 0; t < 1000; ++t) {
		int n = 10, m = 100;

		out.open("disjoint.in"); // deschid fisierul pentru scriere (fisierul.in)
		/* generarea de test */
		vector<int> head(n);
		for (int i = 0; i < n; ++i) {
			head[i] = i;
		}

		out << n << ' ' << m << '\n'; // scriu n, m;

		for (int i = 1; i <= m; ++i) {
			int t = rand() % 10;
			if (t == 0 and head.size() > 1) {
				// sansa de 10% sa adaug o muchie, trebuie sa am cel putin 2 varfuri care nu au parinti
				int x = rand() % (head.size()); // alegem un element random dintre cele care nu au tata

				int a = head[x];
				head[x] = head[head.size() - 1]; // il extragem din sir. Cum ordinea nu conteaza punem pe pozitia aceea ultimul element si dam .pop_back();
				head.pop_back();

				x = rand() % (head.size());
				int b = head[x];
				head[x] = head[head.size() - 1];
				head.pop_back();

				if (rand() % 2) { // legam elementele random
					swap(a, b);
				}
				out << 1 << ' ' << a + 1 << ' ' << b + 1 << '\n'; // indexare de la 0
				head.push_back(a); // il legam pe b de a, sau cel putin presupunem asta
				// am presupun ca b il are ca tata pe a, asa ca il punem inapoi in sir pe a
			} else {
				int x = 0, y = 0;
				while (x == y) {
					x = rand() % n;
					y = rand() % n;
				}
				out << 2 << ' ' << x + 1 << ' ' << y + 1 << '\n';
			}
		}
		out.close(); // trebuie inchis fisierul, sa forteze scrierea

		system("./disjoint"); // rulez sursa buna
		in.open("disjoint.out"); // deschid outputul sursei
		string a = readFromStream(in);

		system("./brut"); // rulez brutul
		in.open("disjoint.out"); // deschid outputul brutului, poate sa fie acelasi
		string b = readFromStream(in);

		if (a != b) {
			cout << "Error!\t" << t << '\n';
			return 0;
		}
        if (t % 100 == 0) {
			cout << "ok\t" << t << '\n'; 
			// afiseaza numarul de teste trecute.
		}
	}
	return 0;
}
