#include <iostream>
#include <vector>
#include <map>

using namespace std;

char winner(char a, char b) {
    if (a == b) {
        return a;
    }

    if (a == 'S') {
        if (b == 'P') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'P') {
        if (b == 'R') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'R') {
        if (b == 'S') {
            return a;
        } else {
            return b;
        }
    }

    return '!';
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i += 1) {
        string rs, ps, ss; cin >> rs >> ps >> ss;
        int r = std::stoi(rs.substr(0, rs.size() - 1));
        int p = std::stoi(ps.substr(0, ps.size() - 1));
        int s= std::stoi(ss.substr(0, ss.size() - 1));

//        cout << "P";
//        p -= 1;
        for (int l = 20; l > 0;) {
            int size = ((1 << l) -1);
            if (p == 1) {
                break;
            }
            if (r >= size) {
                r -= size;
                for (int a = 0; a < size; a += 1) {
                    cout << "R";
                }
                p -= 1;
                cout << "P";
            } else {
                l -= 1;
            }
        }
        cout << "P";
        p -= 1;
        if (p < 0) {
            cerr << "!!\n";
        }
        while (r > 0) {
            cout << "R";
            r -= 1;
        }
        while (p > 0) {
            cout << "P";
            p -= 1;
        }
        while (s > 0) {
            cout << "S";
            s -= 1;
        }

        cout << "\n";
    }
}