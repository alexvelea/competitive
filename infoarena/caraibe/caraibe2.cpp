#include <fstream>
#include <iostream>
using namespace std;

ifstream in("caraibe.in");
ofstream out("caraibe.out");

const int max_n = 65005;
int thr[max_n];

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n - 2; ++i) {
		in >> thr[i];
		// throw
		thr[i] = n - i - thr[i];
	}
	long long rez = 1LL * 100000 * 100000;
	int left = n - 1;
	for (int i = 1; left; ++i) {
		if (thr[i] > left)
			break;
		left -= thr[i];
		rez -= left;
	}
	out << rez << "\n";
	return 0;
}

// Daca ar fi sa ne imaginam totul de la n la 1 .. si ne-am opri atunci toti oameni au fost scosi.
// Daca, ipotetic, avem 2 pirati x si y.
// Lui x ii dam valoarea 0 la momentul 100, inseamna ca la momentul 99 avea o valoare mai mare decat y .. ceea ce inseamna ca inainte de momentul 99 y a fost primul scos.
// De aici deducem ca x un poate fi scos de 2 ori inainte sa il scoatem pe y odata (mergand invers)
// Din acest motiv costul piratilor care il vor influenta pe 1 va fi dat de felul in care ii extragem de la n -> 1
// Acum, nu conteaza efectiv ce pirati "scoatem" -> ii facem 0
// Conteaza ca facem 5 pirati la momentul 5 .. deci o sa ajunga sa aiba costul 5 cand o sa aleaga primul pirat -> costul scade cu 25
