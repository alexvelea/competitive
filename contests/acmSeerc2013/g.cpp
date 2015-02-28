#include <iostream>
#include <fstream>
using namespace std;

const int inf = 0x3f3f3f3f;

int best[3][3], next[3][3];
int n, points[3];

void get_max (int &a, int b) {
	if (a < b)
		a = b;
}

void make_empty() {
    for (int i = 0; i < 3; ++i) {
        points[i] = 0;
        for (int j = 0; j < 3; ++j)
            best[i][j] = next[i][j] = 0;
    }
}

int main() {
    while (cin >> n) {
        
        best[1][1] = best[1][0] = -inf;
        best[0][0] = 0;
        best[0][1] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int a = 0; a < 3; ++a)
                cin >> points[a];
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    next[a][b] = -inf;
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    for (int l = 0; l < 2; ++l) {
                        int s = l + a;
                        if (b)
                            get_max(next[b][l], best[a][b] + points[s]);
                        else
                            get_max(next[b][l], best[a][b]);
                    }
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    best[a][b] = next[a][b];
        }
        int rez = best[1][0];
        get_max(rez, best[0][0]);
        cout << rez << '\n';
        
        make_empty();
    }
	return 0;
}
