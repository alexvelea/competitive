#include <iostream>
using namespace std;

int n, m;
int element[100];
int element_bt[100];

void bt(int element_actual, int nr_elemente) {
	// ne oprim aici cu multimea
	int suma = 0;
	for (int i = 1; i <= nr_elemente; ++i) {
		suma += element_bt[i];
	}

	if (suma == m) {
		for (int i = 1; i < nr_elemente; ++i)
			cout << element_bt[i] << '+';
		cout << element_bt[nr_elemente] << '\n';
	}

	// general in continuare submultimile
	for (int i = element_actual; i <= n; ++i) {
		// punem elementul asta in submultime.
		element_bt[nr_elemente + 1] = element[i];
		bt(i + 1, nr_elemente + 1);
	}
}

int main() {
 	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> element[i];
	}

	bt(1, 0);
	return 0;
}
