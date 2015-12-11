#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

const int kMaxN = 2005;

char s[kMaxN];

int down[kMaxN][kMaxN];
int dir[kMaxN][kMaxN];

void clean(int N, int M) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            down[i][j] = dir[i][j] = numeric_limits<int>::max() / 2;
}

void rotate(vector<string> S){
 	int N = int(S.size());
	int M = int(S[0].size());   
	vector<string> S2(M, string(N, ' '));
	for (int j = 0; j < N; ++j)
    	for (int k = 0; k < M; ++k)
        	S2[k][j] = S[j][M - k - 1];
    S = S2;
}

int main() {
    int N, M;
    freopen("jinxiety.in", "r", stdin);
    freopen("jinxiety.out", "w", stdout);
    while (scanf("%d%d", &N, &M) == 2) {
        if (N == 0 && M == 0)
            break;
        assert(1 <= N && N <= 2000);
        assert(1 <= M && M <= 2000);
        char c;
        scanf("%c", &c);

        vector<string> S(N);
        for (int i = 0; i < N; ++i) {
            fgets(s, sizeof(s), stdin);
            S[i] = s;
            S[i].resize(M);
        }

        int answer = 0;
        for (int p = 0; p < 4; ++p) {
            N = S.size();
            M = S[0].size();

            for (int i = 0; i < N; ++i) {
                auto it = find(S[i].begin(), S[i].end(), '#');
                if (it == S[i].end())
                    continue;
                auto jt = find(S[i].rbegin(), S[i].rend(), '#').base();
                assert(count(it, jt, '#') == jt - it);
            }

            int x[2], y[2] = {1, -1};
            for (int i = 0; i < N; ++i)
                if (count(S[i].begin(), S[i].end(), '#')) {
                    x[0] = x[1] = i;
                    y[0] = find(S[i].begin(), S[i].end(), '#') - S[i].begin();
                    y[1] = find(S[i].rbegin(), S[i].rend(), '#').base() - S[i].begin() - 1;
                    assert(0 <= y[0] && y[0] <= y[1] && y[1] < M);
                    assert(S[x[0]][y[0]] == '#');
                    assert(S[x[1]][y[1]] == '#');
                    break;
                }
            if (y[0] > y[1])
                break;

            clean(N, M);
            down[x[0]][y[0]] = dir[x[0]][y[0]] = 0;
            for (int i = 0; i < N; ++i)
                for (int j = y[0]; j < M; ++j)
                    if (S[i][j] == '#') {
                        if (i > 0) {
                            down[i][j] = min(down[i][j], down[i - 1][j]);
                            dir[i][j] = min(dir[i][j], down[i - 1][j] + 1);
                        }
                        if (j > 0) {
                            down[i][j] = min(down[i][j], dir[i][j - 1] + 1);
                            dir[i][j] = min(dir[i][j], dir[i][j - 1]);
                        }
                        answer = max(answer, min(down[i][j], dir[i][j]));
                    }
            clean(N, M);
            down[x[1]][y[1]] = dir[x[1]][y[1]] = 0;
            for (int i = 0; i < N; ++i)
                for (int j = y[1]; j >= 0; --j)
                    if (S[i][j] == '#') {
                        if (i > 0) {
                            down[i][j] = min(down[i][j], down[i - 1][j]);
                            dir[i][j] = min(dir[i][j], down[i - 1][j] + 1);
                        }
                        if (j + 1 < M) {
                            down[i][j] = min(down[i][j], dir[i][j + 1] + 1);
                            dir[i][j] = min(dir[i][j], dir[i][j + 1]);
                        }
                        answer = max(answer, min(down[i][j], dir[i][j]));
                    }
            assert(answer != numeric_limits<int>::max() / 2);
        	rotate(S);
		}
		if (answer == 1) {
			for (int p = 0; p < 2; ++p) {
	            N = S.size();
    	        M = S[0].size();      				
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < N; ++j) {
						if (i == j)
							continue;
					}
				}
			}
		}
        printf("%d\n", answer);
    }
    return 0;
}
