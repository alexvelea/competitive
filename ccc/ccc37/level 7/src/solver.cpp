#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<char, int> value{
        {'S', 0},
        {'L', 1},
        {'P', 2},
        {'Y', 3},
        {'R', 4},
};

char winner(char a, char b) {
    if (a == b) {
        return a;
    }
    if (value[b] == (value[a] + 1) % 5 || value[b] == (value[a] + 2) % 5) {
        return a;
    } else {
        return b;
    }
}

int main() {
    string s;
    int i = 0;
    while (cin >> s) {
//        cerr << "!" << s[s.size() - 1] << "!\n";
//        if (s[s.size() - 1] < 'A') {
//            s = s.substr(0, s.size() - 1);
//        }
//        cerr << s.size() << '\n';

        string s2 = "";
        while (s.size() > 1) {
            for (int j = 0; j < (int) s.size(); j += 2) {
                s2 += winner(s[j + 0], s[j + 1]);
            }
            cerr << s2 << '\n';
//            cerr << s << '\t' << s2 << '\n';
            s = s2;
            s2 = "";
        }
        i += 1;
        if (s[0] != 'S') {
            cout << "!!\n";
            cerr << "!!\n";
        }
        cout << "#\t" << i << '\t' << s[0] << '\n';
    }
}