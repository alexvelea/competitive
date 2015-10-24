#include <fstream>
using namespace std;
int main() {
    ofstream fout("data.txt");
    int n = 300, q = 1e6;
    fout << n << ' ' << n << ' ';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            fout << abs(rand()) << ' ';
        }
    }
    fout << q << ' ';
    while (q--) {
        int a = rand() % n + 1, b = rand() % n + 1, c = rand() % n + 1, d = rand() % n + 1;
        if (a < c) {
            swap(a, c);
        }
        if (b < d) {
            swap(b, d);
        }
        fout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    }
    return 0;
}
