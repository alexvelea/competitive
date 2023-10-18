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
bool possible[5][5][20][8000];

struct From {
    int a1, x1, a2, x2;
};

From from[5][5][20][8000];

int winner(int a, int b) {
    if (a == b) {
        return a;
    }
    if (b == (a + 1) % 5 || b == (a + 2) % 5) {
        return a;
    } else {
        return b;
    }
}


string solve(int a, int x, int l, int p) {
    if (!possible[a][x][l][p]) {
        cerr << "!!!\n";
    }
    if (l == 0) {
        if (s[p] == 'X') {
            return {valueAt[a]};
        } else if (s[p] == 'Z') {
            return {'Z'};
        } else {
            if (value[s[p]] != a) {
                cerr << "!@#@#@!\n";
            }
            return {s[p]};
        }
    }
    string A = solve(from[a][x][l][p].a1,from[a][x][l][p].x1, l - 1, 2 * p);
    string B = solve(from[a][x][l][p].a2,from[a][x][l][p].x2, l - 1, 2 * p + 1);
    return A + B;
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

        for (int i = 0; i < 5; i += 1) {
            for (int a = 0; a < 5; a += 1) {
                for (int j = 0; j < 20; j += 1) {
                    for (int k = 0; k < 8000; k += 1) {
                        possible[i][a][j][k] = false;
                    }
                }
            }
        }

        for (int i = 0; i < (int) s.size(); i += 1) {
            if (s[i] == 'X') {
                for (int j = 0; j < 5; j += 1) {
                    possible[j][0][0][i] = true;
                }
            } else if (s[i] == 'Z') {
                for (int j = 0; j < 5; j += 1) {
                    possible[j][4][0][i] = true;
                }
            } else {
                possible[value[s[i]]][0][0][i] = true;
            }
        }

        int level = 0;
        while ((1 << (level)) < s.size()) {
            level += 1;
        }

        for (int l = 1; l <= level; l += 1) {
            for (int i = 0; i * (1 << l) < (int) s.size(); i += 1) {
                for (int a1 = 0; a1 < 5; a1 += 1) {
                    for (int x1 = 0; x1 < 5; x1 += 1) {
                        if (!possible[a1][x1][l - 1][2 * i]) {
                            continue;
                        }

                        for (int a2 = 0; a2 < 5; a2 += 1) {
                            for (int x2 = 0; x2 < 5; x2 += 1) {
                                if (!possible[a2][x2][l - 1][2 * i + 1]) {
                                    continue;
                                }

                                bool forced[5] = {false, false, false, false, false};
                                for (int y1 = 0; y1 <= x1; y1 += 1) {
                                    for (int y2 = 0; y2 <= x2; y2 += 1) {
                                        forced[winner((a1 + y1) % 5, (a2 + y2) % 5)] = true;
                                    }
                                }

                                // find first zero
                                int o = 0;
                                while (o < 5 && !forced[o]) {
                                    o++;
                                }
                                if (o == 5) {
                                    cerr << "ERROR o\n";
                                    continue;
                                }

                                int a = o, b = o;
                                while (a > -10 && forced[(a + 15) % 5]) {
                                    a -= 1;
                                }
                                if (a == -10) {
                                    for (int s = 0; s < 5; s += 1) {
                                        possible[s][4][l][i] = true;
                                        from[s][4][l][i] = From{
                                                a1: a1,
                                                x1: x1,
                                                a2: a2,
                                                x2: x2,
                                        };
                                    }
                                    continue;
                                }

                                a = (a + 15 + 1) % 5;

                                b = a;
                                while (forced[(b + 5) % 5]) {
                                    b += 1;
                                }

                                int x = (b - a - 1 + 10) % 5;
//                                cerr << forced[0] << forced[1] << forced[2] << forced[3] << forced[4] << '\t' << a
//                                     << '\t' << x << '\t' << l << '\t' << i << '\n';
                                possible[a][x][l][i] = true;
                                from[a][x][l][i] = From{
                                        a1: a1,
                                        x1: x1,
                                        a2: a2,
                                        x2: x2,
                                };
                            }
                        }
                    }
                }
            }
        }

        cout << solve(0, 0, level, 0) << '\n';
    }
}