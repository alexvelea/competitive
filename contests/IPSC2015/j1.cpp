#include <iostream>
using namespace std;
int main() {
    for (int i = 0; i < 100; ++i) {
        cerr << i << '\t' << char(i) << '\n';
    }
    return 0;
}
