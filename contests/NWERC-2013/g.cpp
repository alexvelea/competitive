//Problem g @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int a, b, c;
    
    while (cin >> a >> b >> c) {
        int x = a * b;
        int y = c - b;
        int g = __gcd(x, y);
        cout << x / g << '/' << y / g << '\n';
    }
	return 0;
}
