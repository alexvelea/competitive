#include <fstream>
using namespace std;

const int kMaxN = 1e6;

int a[kMaxN];

int main() {
    ifstream fin("data.txt");
    int n; fin >> n;
    for (int i = 1; i <= n; ++i) {
        fin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        }
    }
    return 0;
}
