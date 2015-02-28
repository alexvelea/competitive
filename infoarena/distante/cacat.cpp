#include <cstdio>
#include <cstring>
#define N 50001
 
int n, m, T;
int source;
int d[N];
 
int main() {
    freopen ("distante.in", "r", stdin);
    freopen ("distante.out", "w", stdout);
    scanf ("%d\n", &T);
    int i,p, q, c, ok = 1;
    while (T--) {
        scanf ("%d %d %d\n", &n, &m, &source);
        for (i = 1; i <= n; ++i)
            scanf ("%d ", &d[i]);
        ok = 1;
        while (m--) {
            scanf ("%d %d %d\n", &p, &q, &c);
            if (d[p] > d[q] + c || d[q] > d[p] + c)
                ok = 0;
        }
         
        if (d[source] != 0)
            ok = 0;
        printf ("%s\n", ok == 1 ? "DA" : "NU");
    }
    return 0;
}
