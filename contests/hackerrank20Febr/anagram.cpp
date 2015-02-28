#include <cmath>

#include <iostream>
#include <string>
using namespace std;

string a, b;
int viz[26];

int main() {
	cin >> a >> b;
	for (int i = 0; i < int(a.size()); ++i)
		viz[a[i] - 'a']++;
	for (int i = 0; i < int(b.size()); ++i)
		viz[b[i] - 'a']--;
	int rez = 0;
	for (int i = 0; i < 26; ++i)
		rez += abs(viz[i]);
	cout << rez << '\n';
	return 0;
}
