#include <fstream>
#include <iomanip>
#include <cstdio>
 
#define MAX 305
 
using namespace std;
 
int N, M, R, C;
int A[MAX][MAX];
double ans, rez;
 
void citire() {
    ifstream in("balans.in");
    in>>N>>M>>R>>C;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++) {
            in>>A[i][j];
            A[i + N][j] = A[i][j + M] = A[i + N][j + M] = A[i][j];
        } in.close();
    for(int i = 1; i <= 2 * N; i++)
        for(int j = 1; j <= 2 * M; j++)
            A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
}
int penis=0;
void solve() {
    for(int r = max(R, 1); r <= N; r++)
        for(int c = max(C, 1); c <= M; c++)
            for(int i = N + 1; i <= 2 * N; i++)
                for(int j = M + 1; j <= 2 * M; j++) {
 					penis++;
                    rez = A[i][j] - A[i][j - c] - A[i - r][j] + A[i - r][j - c];
                    if(rez > ans * r * c)
                        ans = rez / (1.0 * r * c);
                }
}
 
void afisare() {
//    freopen("balans.out", "w", stdout);
	printf("%d-->\n",penis);
    printf("%.3lf", (int(ans * 1000)) / 1000.0);
    fclose(stdout);
}
 
int main() {
    citire();
    solve();
    afisare();
    return 0;
}
