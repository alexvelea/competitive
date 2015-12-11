#include <iostream>
using namespace std;
int main() {
	pair<int, int> a, b;
	a = make_pair(1, 2);
	b = make_pair(200, 300);
	a += b;
	cout << a.first << '\t' << a.second;
}
