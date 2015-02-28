#include <iostream>
#include <vector>
using namespace std;
int main() {
	vector<int> a;
	a.reserve(10);
	cout << a.capacity() << "\n";
	return 0;
}
