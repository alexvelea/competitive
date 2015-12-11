#include <cassert>
 
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
 
#define FORIT(it,v) for(vector<int> :: iterator it = (v).begin(); it != (v).end(); ++it)
 
ifstream in("parb.in");
ofstream out("parb.out");
 
const int max_n = 100005;
const int log_n = 17;
const int MOD = 1000000009, sigma = 37;
int sigma_p[30];
 
vector<int> vertex[max_n];
int n;
char el[max_n];
 
bool viz[max_n], chain_start[max_n];
int deep[max_n], leaf[max_n];
int down[max_n][log_n], hash_down[max_n][log_n];
 
void get_min (int &a, int b) {
    if (a > b)
        a = b;
}
 
int codif (char c) {
    return c - 'a' + 1;
}
 
void get_deep (int nod) {
    if (viz[nod])
        return ;
    viz[nod] = true;
    FORIT (it, vertex[nod])
        if (!viz[*it]) {
            deep[*it] = deep[nod] + 1;
            get_deep(*it);
        }
}
 
bool comp_chain (int a, int b) {
    // a > b?
    int n1 = deep[leaf[a]] - deep[a] + 1;
    int n2 = deep[leaf[b]] - deep[b] + 1;
    int n = min (n1, n2);    // n reprezinta distanta celui mai scurt lant
    int p = 0, poz = 0; // poz e cat de mult se potrivesc cele 2 situri
    for (; (1<<p) <= n; ++p)
        ;
    --p;
    for (; p>=0; --p)
        if (poz + (1<<p) <= n) {
            if (hash_down[a][p] == hash_down[b][p]) {
                a = down[a][p];
                b = down[b][p];
                poz += (1<<p);
            }
        }
    if (poz == n) {
        if (n1 == n2)
            return 1;
        if (n1 == n)
            return 0;
        return 1;
    }
    return el[a] > el[b];
}
 
void make_down (int i) {
    for (int p = 1; (1<<p) <= n; ++p) {
        down[i][p] = down[down[i][p-1]][p-1];
        hash_down[i][p] = (1LL * sigma_p[p-1] * hash_down[i][p-1] + hash_down[down[i][p-1]][p-1] ) % MOD;
    }
}
 
void make_chain (int nod) {
    hash_down[nod][0] = codif(el[nod]);
    int nr = 0;
    FORIT (it,vertex[nod]) {
        if (deep[*it] == deep[nod]+1) {
            make_chain(*it);
            nr++;
        }
    }
    if (nr == 0) {
        leaf[nod] = nod;
        return ;
    }
    if (nr == 1) {
        leaf[nod] = leaf[vertex[nod].back()];
        down[nod][0] = vertex[nod].back();
        make_down(nod);
        return ;
    }
    // trebuie sa gasim cel mai bun lant
    nr = 0;
    int target;
    FORIT (it, vertex[nod]) {
        if (deep[*it] != deep[nod] + 1)
            continue;
        if (nr == 0) {
            target = *it;
            nr = 1;
            continue;
        }
        if (comp_chain(*it, target))
            target = *it;
    }
    leaf[nod] = leaf[target];
    down[nod][0] = target;
    make_down(nod);
    return ;
}
 
int pow (int x, int p) {
    int rez = 1;
    while (p) {
        if (p&1)
            rez = (1LL * rez * x) % MOD;
        x = (1LL * x * x) % MOD;
        p >>= 1;
    }
    return rez;
}
 
int main() {
    in >> n;
    assert (n < max_n);
    for (int p = 0; (1<<p) <= n; ++p)
        sigma_p[p] = pow(sigma, (1<<p));
    in >> el;
    for (int i = n; i; --i)
        el[i] = el[i-1];
    for (int i = 1; i < n; ++i) {
        int a, b;
        in >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    deep[1] = 1;
    get_deep(1);
    make_chain(1);
    chain_start[1] = true;
        int target = 1;
    for (int i = 2; i <= n; ++i)
        if (comp_chain(i, target))
            target = i;
   while (target != 0) {
       out << el[target];
       target = down[target][0];
    }
    return 0;
}
