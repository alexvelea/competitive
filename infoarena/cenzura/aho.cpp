#include <cstring>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Trie
{
    int clicks;
    bool done;
    Trie *nxt[26], *back;
    vector<Trie*> W;
    
    Trie()
    {
        memset(nxt, 0, sizeof(nxt));
        back = 0;
        clicks = 0;
        done = false;
    }
};
Trie *R = new Trie;

int root;
Trie *where[102];

void insertT(Trie *T, char *now)
{
    if (*now == 0)
    {
        where[root] = T;
        return;
    }
    if (T->nxt[*now - 'a'] == 0)
        T->nxt[*now - 'a'] = new Trie();
    insertT(T->nxt[*now - 'a'], now + 1);
}

char A[1000002], B[10002];
int N;
queue<Trie*> Q;

void Dfs(Trie *T)
{
    T->done = true;
    for (auto it = T->W.begin(); it != T->W.end(); ++it)
    {
        if (!(*it)->done)
            Dfs(*it);
        T->clicks += (*it)->clicks;
    }
}

int main()
{
    ifstream fin("aho.in");
    ofstream fout("aho.out");
    
    fin >> A;
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> B;
        
        root = i;
        insertT(R, B);
    }
    
    Q.push(R);
    while (!Q.empty())
    {
        Trie *now = Q.front();
        Q.pop();
        
        for (int i = 0; i < 26; ++i)
            if (now->nxt[i] != 0)
            {
                Trie *aux = now->back;
                
                while (aux != 0 && aux->nxt[i] == 0)
                    aux = aux->back;
                
                if (aux == 0)
                {
                    now->nxt[i]->back = R;
                    R->W.push_back(now->nxt[i]);
                }
                else
                {
                    now->nxt[i]->back = aux->nxt[i];
                    aux->nxt[i]->W.push_back(now->nxt[i]);
                }
                
                Q.push(now->nxt[i]);
            }
    }
    
    Trie *tnow = R;
    for (int i = 0; A[i] != 0; ++i)
    {
        while (tnow != 0 && tnow->nxt[A[i] - 'a'] == 0)
            tnow = tnow->back;
        
        if (tnow == 0) tnow = R;
        else           tnow = tnow->nxt[A[i] - 'a'];
        
        ++tnow->clicks;
    }
    
    
    Dfs(R);
    
    for (int i = 1; i <= N; ++i)
        fout << where[i]->clicks << '\n';
    
    fin.close();
    fout.close();
}
