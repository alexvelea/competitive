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

string valueAt = "SLPYR";

string s;
bool possible[5][20][8000];

string solve(int l, int i, int p) {
    if (l == 0) {
        if (s[i] == 'X') {
            return {valueAt[p]};
        } else {
            if (value[s[i]] != p) {
                cerr << "!@#@#@!\n";
            }
            return {s[i]};
        }
    }

    if ((possible[p][l - 1][2 * i]) && (possible[(p) % 5][l - 1][2 * i + 1] | possible[(p + 1) % 5][l - 1][2 * i + 1] | possible[(p + 2) % 5][l - 1][2 * i + 1])) {
        string a = solve(l - 1, 2 * i, p);
        if (possible[(p) % 5][l - 1][2 * i + 1]) {
            a = a + solve(l - 1, 2 * i + 1, p);
        } else if (possible[(p + 1) % 5][l - 1][2 * i + 1]) {
            a = a + solve(l - 1, 2 * i + 1,  (p + 1) % 5);
        } else if (possible[(p + 2) % 5][l - 1][2 * i + 1]) {
            a = a + solve(l - 1, 2 * i + 1,  (p + 2) % 5);
        } else {
            cerr << "!!\n";
        }
        return a;
    } else {
        string a = "";
        if (possible[(p) % 5][l - 1][2 * i]) {
            a = a + solve(l - 1, 2 * i, p);
        } else if (possible[(p + 1) % 5][l - 1][2 * i]) {
            a = a + solve(l - 1, 2 * i,   (p + 1) % 5);
        } else if (possible[(p + 2) % 5][l - 1][2 * i]) {
            a = a + solve(l - 1, 2 * i,   (p + 2) % 5);
        } else {
            cerr << "!!\n";
        }

        a = a + solve(l - 1, 2 * i + 1, p);
        return a;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int M = 0;
    while ((1 << M) < m) {
        M += 1;
    }

    while (n--) {

        cin >> s;
//        cerr << "Solving for\t" << s << '\n';

        for (int i = 0; i < 5; i += 1) {
            for (int j = 0; j < 20; j += 1) {
                for (int k = 0; k < 8000; k += 1) {
                    possible[i][j][k] = false;
                }
            }
        }

        for (int i = 0; i < (int)s.size(); i += 1) {
            if (s[i] == 'X') {
                for (int j = 0; j < 5; j += 1) {
                    possible[j][0][i] = true;
                }
            } else {
                possible[value[s[i]]][0][i] = true;
            }
        }

        int level = 0;
        while ((1 << (level)) < s.size()) {
            level += 1;
        }

        for (int l = 1; l <= level; l += 1) {
            for (int i = 0; i * (1 << l) < (int)s.size(); i += 1) {
                for (int p = 0; p < 5; p += 1) {
                    // left wins
                    if (possible[p][l - 1][2 * i]) {
                        possible[p][l][i] = (possible[(p) % 5][l - 1][2 * i + 1] | possible[(p + 1) % 5][l - 1][2 * i + 1] | possible[(p + 2) % 5][l - 1][2 * i + 1]);
                    }

                    // right wins
                    if (possible[p][l - 1][2 * i + 1]) {
                        possible[p][l][i] = (possible[(p) % 5][l - 1][2 * i] |possible[(p + 1) % 5][l - 1][2 * i] | possible[(p + 2) % 5][l - 1][2 * i]);
                    }
                }
            }
        }


        cout << solve(level, 0, 0) << '\n';
//        for (int l = 0; l <= level; l += 1) {
//            for (int i = 0; i * (1 << l) < (int)s.size(); i += 1) {
//                cout << possible[0][l][i];
//            }
//            cout << '\n';
//        }
//        cout << "!!!\n";
//
//        cout << possible[0][level][0] << '\n';
//        int z = 0;
//        while ((1 << (z + 1)) <= num[0]) {
//            z += 1;
//        }
//        num[0] -= (1 << z);
//        for (int i = M - 1; i >= z; i -= 1) {
//            win(i);
//            cerr << "!\n";
//        }
//        num[0] += (1 << z);
//        for (int i = 0; i < (1 << z); i += 1) {
//            put(0);
//        }

//        cerr << '\n';
//        for (int i = 0; i < 5; i += 1) {
//            cerr << i << '\t' << num[i] << '\n';
//        }

//
//        int level = 4;
//        bool failed = false;
//        while (level >= 3 && failed == false) {
//
//            // finish level
//            if (num[level] == 0) {
//                level -= 1;
//                continue;
//            }
//
//            for (int i = 20; i > 0;) {
//                int size = ((1 << i) - 1);
//                if (num[level - 1] + num[level - 2] == 1) {
//                    failed = true;
//                    break;
//                }
//
//                if (num[level] >= size) {
//                    while (size--) {
//                        put(level);
//                    }
//                    if (num[level - 1] == 0) {
//                        put(level - 2);
//                    } else {
//                        put(level - 1);
//                    }
//                } else {
//                    i -= 1;
//                }
//            }
//        }
//
//        if (level == 4) {
//            if (num[level - 1] == 0) {
//                put(level - 2);
//            } else {
//                put(level - 1);
//            }
//            while (num[4]) {
//                put(4);
//            }
//            level -= 1;
//        }
//        if (level == 3) {
//            if (num[level - 1] == 0) {
//                put(level - 2);
//            } else {
//                put(level - 1);
//            }
//            while (num[3]) {
//                put(3);
//            }
//            level -= 1;
//        }
//
    }
}