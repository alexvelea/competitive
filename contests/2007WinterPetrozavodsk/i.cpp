#include <fstream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

ifstream fin("transform.in");
ofstream fout("transform.out");

map<char, int> H ={{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

int main() {
    string a, b; fin >> a >> b;
    vector<int> e(a.size(), 0);

    for (int i = 0; i < int(a.size()); ++i) {
        e[i] = (4 - ((H[b[i]] - H[a[i]] + 4) % 4)) % 4;
    }
    e.push_back(0);

    vector<tuple<int, int, int> > rez;

    for (int i = 0; i + 1 < int(e.size()); ++i) {
        if (e[i] == 0) {
            continue;
        }

        int d = (4 - e[i]);
        int where = i;
        while (e[where] == e[i] and where + 1 < int(e.size())) {
            where++;
        }
        where--;

        for (int j = i + 1; j + 1 < int(e.size()); ++j) {
            if ((e[j] + d) % 4 == e[j + 1]) {
                where = j;
                break;
            }
        }
        rez.push_back(make_tuple(i, where, d));
        for (int j = i; j <= where; ++j) {
            e[j] += d;
            e[j] %= 4;
        }
    }
    fout << rez.size() << '\n';
    for (auto itr : rez) {
        int st, dr, d;
        tie(st, dr, d) = itr;
        fout << st + 1 << ' ' << dr + 1 << ' ' << d << '\n';
    }
    return 0;
}
