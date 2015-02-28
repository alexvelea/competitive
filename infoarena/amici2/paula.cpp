#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

ifstream fin("amici2.in");
ofstream fout("amici2.out");

const int MAXN = 21009;

int N, M, T, d[MAXN], diametru;
vector < int > G[MAXN];
queue < int > coada;
bool used[MAXN];

inline void citire()
{
    int x, y;
    
    fin >> N >> M;
    for (int i = 1; i <= N; ++i)
        G[i].clear();
    for (int i = 0; i < M; ++i)
    {
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

inline void initializare()
{
    diametru = 0;
    
    for (int i = 1; i <= N; ++i)
    {
        used[i] = false;
        d[i] = INT_MAX;
    }
}

inline int maxim (int a, int b)
{
    if ( a > b )
        return a;
    return b;
}

inline void BFS (int tata)
{
    coada.push(tata);
    used[tata] = true;
    d[tata] = 0;
    
    while ( !coada.empty() )
    {
        int nod = coada.front();
        coada.pop();
        
        int L = G[nod].size();
        for (int i = 0; i < L; ++i)
        {
            int fiu = G[nod][i];
            if ( !used[fiu] )
            {
                used[fiu] = true;
                coada.push(fiu);
                d[fiu] = d[nod] + 1;
                diametru = maxim (diametru, d[fiu]);
            }
        }
    }
}

int main ()
{
    fin >> T;
    for (int i = 0; i < T; ++i)
    {
        citire();
        initializare();
        BFS((rand() % N) + 1);
        int rasp ;
        for ( rasp = 0; (1 << rasp) < diametru; ++rasp);
        fout << rasp << "\n";
    }
    
    fin.close();
    fout.close();
    
    return 0;
}
