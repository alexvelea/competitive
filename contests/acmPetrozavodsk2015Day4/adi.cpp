#include <iostream>
#include <fstream>

using namespace std;

int dp[66][66][66][66];
int C[5], L[5];

inline void getMin(int &a, int b) {
    a = (a > b) ? b : a;
}

int main() {
    ifstream cin("dirichlet.in");
    ofstream cout("dirichlet.out");
    int T, N; cin >> T >> N;
    
    int total = 0;
    for (int i = 0; i < T; ++i) {
        cin >> C[i] >> L[i];
        total += C[i] * L[i];
    }
    
    if (total % N) {
        cout << "No\n";
        return 0;
    }
    int row = total / N;
    
    for (int i = 0; i < 65; ++i)
        for (int j = 0; j < 65; ++j)
            for (int k = 0; k < 65; ++k)
                for (int p = 0; p < 65; ++p)
                    dp[i][j][k][p] = 65;
    dp[0][0][0][0] = 0;
    for (int V = 0; V < N; ++V) {
        for (int a = 0; a <= C[0]; ++a)
            for (int b = 0; b <= C[1]; ++b)
                for (int c = 0; c <=C[2]; ++c)
                    for (int d = 0; d <= C[3]; ++d) {
                        if (dp[a][b][c][d] > C[4])
                            continue;
                        getMin(dp[a + 1][b][c][d], dp[a][b][c][d]);
                        getMin(dp[a][b + 1][c][d], dp[a][b][c][d]);
                        getMin(dp[a][b][c + 1][d], dp[a][b][c][d]);
                        getMin(dp[a][b][c][d + 1], dp[a][b][c][d]);
                        int sum = row * (V + 1) - a * L[0] - b * L[1] - c * L[2] - d * L[3];
                        if (L[4] == 0) {
                            if (sum == 0)
                                dp[a][b][c][d] = 0;
                            else
                                dp[a][b][c][d] = 65;
                        } else {
                            if (sum >= 0 && sum % L[4] == 0 && sum / L[4] >= dp[a][b][c][d])
                                dp[a][b][c][d] = sum / L[4];
                            else
                                dp[a][b][c][d] = 65;
                        }
                    }
    }
    
    if (dp[C[0]][C[1]][C[2]][C[3]] == C[4]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
