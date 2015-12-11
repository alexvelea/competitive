#include <fstream>
using namespace std;

ofstream fout("data.txt");

int main() {
    int n = int(1e5);
    fout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        fout << rand() << '\n';
    }
}
