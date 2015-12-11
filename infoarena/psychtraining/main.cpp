#include <fstream>
#include <unordered_map>
#include <string>
using namespace std;

ifstream fin("psychtraining.in");
ofstream fout("psychtraining.out");

int main() {
    int n; fin >> n;
    fout << 9 << '\n';
    for (int t = 0; t < 9; t += 1) {
        string current_row = "";
        unordered_map<int, char> ch = { {0, 'a'}, {1, 'b'} };
        for (int i = 1; i <= n; i += 1) {
            current_row += ch[(i & (1 << t)) == 0];
        }
        fout << current_row << '\n';
    }
    return 0;
}
