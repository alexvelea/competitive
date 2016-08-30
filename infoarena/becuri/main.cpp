#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 505, kInvalidMoves = 2*kMaxN+5;

bool el[kMaxN][kMaxN];

vector<pair<int, int>> Solve(int r, int c, bool flip_first_row) {
    bool matrix[r + 1][c + 1];
    for (int i = 1; i <= r; i += 1) {
        for (int j = 1; j <= c; j += 1) {
            matrix[i][j] = el[i][j];
        }
    }

    vector<pair<int, int>> moves;

    if (flip_first_row) {
        for (int j = 1; j <= c; j += 1) {
            matrix[1][j] ^= 1;       
        }

        int pos = 1;
        for (int j = 1; j <= c; j += 1) {
            if (matrix[1][j] == 1) {
                pos = j;
                break;
            }
        }

        for (int i = 1; i <= r; i += 1) {
            matrix[i][pos] ^= 1;
        }

        moves.push_back({1, pos});
    }

    vector<int> column_indices, line_indices;
    for (int j = 1; j <= c; j += 1) {
        if (matrix[1][j] == 1) {
            column_indices.push_back(j);
        }
    }

    for (int i = 2; i <= r; i += 1) {
        if ((matrix[i][1] ^ matrix[1][1]) == 1) {
            line_indices.push_back(i);
        }
    }

    if (line_indices.size() % 2 != column_indices.size() % 2) {
        moves.resize(kInvalidMoves);
        return moves;
    }

    for (int i = 0, j = 0; i < (int)max(line_indices.size(), column_indices.size()); i += 1, j += 1) {
        int line = 0, column = 0;
        if (i < (int)line_indices.size()) {
            line = line_indices[i];
        } else {
            line = 1;
        }

        if (j < (int)column_indices.size()) {
            column = column_indices[j];
        } else {
            column = 1;
        }

        moves.push_back({line, column});
    }

    return moves;
}

int main() {
    ifstream cin("becuri.in");
    ofstream cout("becuri.out");

    int r, c; cin >> r >> c;
    for (int i = 1; i <= r; i += 1) {
        for (int j = 1; j <= c; j += 1) {
            cin >> el[i][j];           
        }
    }
    
    vector<pair<int, int>> a, b;

    a = Solve(r, c, false);
    b = Solve(r, c, true);

    if (a.size() > b.size()) {
        a = b;
    }

    if ((int)a.size() == kInvalidMoves) {
        cout << "-1\n";
    } else {
        cout << a.size() << '\n';
        for (auto itr : a) {
            cout << itr.first << ' ' << itr.second << '\n';
        }
    }

    return 0;
}
