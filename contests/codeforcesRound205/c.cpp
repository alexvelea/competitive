#include <iostream>
#include <vector>
using namespace std;

vector<int> poz[100];
int where[205];
int inside[3], rez = 0;
int T[205], viz[205];

int main() {
	int n;
	cin >> n;
 	for (int i = 1; i <= 2 * n; ++i) {
		cin >> T[i];
		viz[T[i]]++;
		poz[T[i]].push_back(i);
	}
	for (int i = 10; i <= 99; ++i) {
		if(viz[i] >= 2) {
			where[poz[i][0]] = 1;
			where[poz[i][1]] = 2;
			rez += inside[2];
			inside[1] ++;
			rez += inside[1];
			inside[2] ++;
		}
	}
	for (int i = 10; i <= 99; ++i) {
		if (viz[i] == 1) {
			if (inside[1] <= inside[2]) {
				rez += inside[2];
            	inside[1] ++;
 				where[poz[i][0]] = 1;
			} else {
				rez += inside[1];
				inside[2] ++;
				where[poz[i][0]] = 2;
			}
		}
	}
	for (int i = 10; i <= 99; ++i) {
		for (int j = 2; j < int(poz[i].size()); ++j) {
			if (inside[1] < n) {
				inside[1] ++;
				where[poz[i][j]] = 1;
			} else {
				where[poz[i][j]] = 2;
			}
		}
	}
	cout << rez << '\n';
	for (int i = 1; i <= 2 * n; ++i)
		cout << where[i] << ' ';
	return 0;
}
