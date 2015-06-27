#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
using namespace std;

const int kMaxVal = 3e6+5, kMaxN = 3e4 + 5;

#define int64 long long

unordered_map<string, int> wordsValue, vizInsult;
vector<pair<string, int> > words[3];

ifstream fin("b2.in");
ofstream fout("b1.out");

void read(int ind) {
    int n; fin >> n;
    while (n--) {
        string txt; fin >> txt;
        int cost; fin >> cost;
        wordsValue[txt] = cost;
        words[ind].push_back(make_pair(txt, cost));
    }
}

int required[kMaxN];

const int kMagicNumber = 32;
struct myStr {
    int el[3];
    myStr() {
        el[0] = el[1] = el[2] = 0;
    }
} aux;
vector<myStr> from[3][kMaxVal];

int main() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < kMaxVal; ++j) {
            from[i][j].reserve(kMagicNumber);
        }
    }
    cerr << "StartRead\n";
    read(0);
    read(1);
    read(2);
    cerr << "EndRead\n";

    int q; fin >> q;
    int mx = 0;
    for (int i = 0; i < q; ++i) {
        string txt, final = "";
        int cost = 0;
        for (int j = 0; j < 3; ++j) {
            fin >> txt;
            final += txt + ' ';
            cost += wordsValue[txt];
        }
        required[i] = cost + 1;
        vizInsult[final] = true;
    }
    cerr << mx << '\n';

    {int i = 0;
    for (auto itr : words[0]) {
        if (from[0][itr.second].size() < kMagicNumber) {
            aux.el[0] = i;
            from[0][itr.second].push_back(aux);
        }
        ++i;
    }}
   
    int expected = 2 * kMaxVal;
    int now = 0;

    for (int l = 1; l < 3; ++l) {
        for (int val = 0; val < kMaxVal; ++val) {
            ++now;
            if (now % 100000 == 0) {
                cerr << fixed << setprecision(10) << 1.0 * now / expected << '\n';
            }
            for (int itr = 0; itr < int(words[l].size()) and from[l][val].size() < kMagicNumber; ++itr) {
                int cost = val - words[l][itr].second;
                if (cost < 0) {
                    continue;
                }

                for (int itr2 = 0; itr2 < int(from[l - 1][cost].size()) and from[l][val].size() < kMagicNumber; ++itr2) {
                    from[l - 1][cost][itr2].el[l] = itr;
                    from[l][val].push_back(from[l - 1][cost][itr2]);
                }
            }
        }
    }
    cerr << "FINISHED!\n";

    for (int i = 0; i < q; ++i) {
        int cost = required[i];
        string final = "";
        while (1) {
            if (from[2][cost].size() == 0) {
                cerr << "PANIICCC\n";
            }

            final = words[0][from[2][cost].back().el[0]].first + ' ' + 
                    words[1][from[2][cost].back().el[1]].first + ' ' + 
                    words[2][from[2][cost].back().el[2]].first + ' ';
            from[2][cost].pop_back();
            if (vizInsult[final] == true) {
                ;
            } else {
                break;
            }
        }
        fout << final << '\n';
    }
    return 0;
}
