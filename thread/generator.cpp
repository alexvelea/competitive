#include <fstream>
using namespace std;
int main() {
    ofstream fout("rawData.txt");
    int n = 1e5;
    fout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        fout << rand() << '\n';
    }
    return 0;
}
