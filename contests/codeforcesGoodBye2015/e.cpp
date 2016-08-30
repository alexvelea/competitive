//Problem e @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

#define int64 long long

int solve(vector<int> av, vector<int> howMany) {
	for (int i = 0; i < 3; i += 1) {
		for (int j = i; j >= 0; j -= 1) {
			int x = min(howMany[j], av[i]);
			howMany[j] -= x;
			av[i] -= x;
		}
	}

	int currentRez = 0;
	int required;

	required = howMany[2];
	currentRez += required;

	av[0] += required;
	av[1] += required;
	av[2] += required;

	for (int i = 0; i < 3; i += 1) {
		for (int j = i; j >= 0; j -= 1) {
			int x = min(howMany[j], av[i]);
			howMany[j] -= x;
			av[i] -= x;
		}
	}

	required = int(howMany[1] + 1) / 2;
	currentRez += required;

	av[0] += required;
	av[1] += required;
	av[2] += required;

	for (int i = 0; i < 3; i += 1) {
		for (int j = i; j >= 0; j -= 1) {
			int x = min(howMany[j], av[i]);
			howMany[j] -= x;
			av[i] -= x;
		}
	}

	required = int(howMany[0] + 2) / 3;
	currentRez += required;

	av[0] += required;
	av[1] += required;
	av[2] += required;

	for (int i = 0; i < 3; i += 1) {
		for (int j = i; j >= 0; j -= 1) {
			int x = min(howMany[j], av[i]);
			howMany[j] -= x;
			av[i] -= x;
		}
	}

	return currentRez;
}

int main() {
	ios::sync_with_stdio(false);
	int m; cin >> m;
	int a, b, c; cin >> a >> b >> c;
	vector<int> elements = {a, b, c};
	sort(elements.begin(), elements.end());
	a = elements[0];
	b = elements[1];
	c = elements[2];

	
	vector<int> target(m, 0);
	for (int i = 0; i < m; i += 1) {
		cin >> target[i];
	}

	sort(target.begin(), target.end());

	// cerr << a << '\t' << b << '\t' << c << '\n';

	if (a + b >= c) {
		vector<int> order = {a, b, c, a + b, c + a, c + b, a + b + c};
		vector<int> howMany(order.size(), 0);
		int current = 0;
		for (int itr : target) {
			while (current < int(order.size()) and itr > order[current]) {
				current += 1;
			}
			// cerr << itr << '\t' << current << "!!\n";

			if (current == int(order.size())) {
				cout << "-1\n";
				return 0;
			}

			howMany[current] += 1;
		}

		// for (auto itr : howMany) {
			// cerr << itr << '\n';
		// }

		int rez = howMany[6] + howMany[5] + howMany[4] + howMany[3];
		int mn = inf;
		vector<int> av = {howMany[5], howMany[4], howMany[3]};
		for (int AB = 0; AB <=howMany[2]; AB += 1) {
			auto aux = av;
			aux[2] += 2 * AB;
			mn = min(mn, AB + solve(aux, howMany));
		}	
		cout << mn + rez << '\n';
	} else {
		vector<int> order = {a, b, a + b, c, c + a, c + b, a + b + c};
		vector<int> howMany(order.size(), 0);
		int current = 0;
		for (int itr : target) {
			while (current < int(order.size()) and itr > order[current]) {
				current += 1;
			}

			if (current == int(order.size())) {
				cout << "-1\n";
				return 0;
			}

			howMany[current] += 1;
		}

		int rez = howMany[6] + howMany[5] + howMany[4] + howMany[3];
		int mn = inf;
		int avAB = howMany[3];
		vector<int> av = {howMany[5], howMany[4], 0};
		for (int AB = 0; AB <= avAB + howMany[2]; AB += 1) {
			auto aux = av;
			aux[0] += max(0, avAB - AB);
			aux[1] += max(0, avAB - AB);
			aux[2] += AB + max(0, AB - avAB);
			mn = min(mn, max(0, AB - avAB) + solve(aux, howMany));
		}	
		cout << mn + rez << '\n';
	}
	return 0;
}