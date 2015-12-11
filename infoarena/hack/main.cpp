#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int n = 25, N = 2 * n;

class Edge {
  public:
    int a, b, c;
    int id;
    pair<int, int> position;
    static int next_id;
  public:
    bool apm_selected;

    Edge(int _a, int _b, int _c, pair<int, int> _position) : a(_a), b(_b), c(_c), position(_position) {
        id = next_id++;
        apm_selected = false;
    }

    int other(int nod) {
        return a + b - nod;
    }

    int getCost() {
        return c;
    }

    int getId() {
        return id;
    }

    pair<int, int> getVertices() {
        return {a, b};
    }

    pair<int, int> getPosition() {
        return position;
    }

    bool operator < (const Edge &rhs) const{
        return c < rhs.c;
    }
};

int Edge::next_id = 0;

class DisjointDataset {
  public:
    vector<int> father;
  public:
    DisjointDataset(int n) {
        father.resize(n + 1);
        for (int itr = 0; itr < int(father.size()); itr += 1) {
            father[itr] = itr;
        }
    }

    int getFather(int nod) {
        if (father[nod] != nod) {
            father[nod] = getFather(father[nod]);
        }
        return father[nod];
    }

    int Union(int a, int b) {
        if (rand() % 2) {
            swap(a, b);
        }
        a = getFather(a);
        b = getFather(b);
        father[a] = b;
        return b;
    }

    inline int Union(pair<int, int> a) {
        return Union(a.first, a.second);
    }

    bool sameUnion(int a, int b) {
        return (getFather(a) == getFather(b));
    }

    inline bool sameUnion(pair<int, int> a) {
        return sameUnion(a.first, a.second);
    }
} copaci(n * n);

int num[n][n];
vector<int> adjacent_edges[n * n];
vector<Edge> edge_list;
char final_matrix[N][N];

void addEdge(int a, int b, int c, pair<int, int> position) {
    edge_list.push_back(Edge(a, b, c, position));
    adjacent_edges[a].push_back(edge_list.rbegin()->getId());
    adjacent_edges[b].push_back(edge_list.rbegin()->getId());
}

int main() {
    srand(time(NULL));
    for (int s = 0, i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1, s += 1) {
            num[i][j] = s;
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (i + 1 < n) {
                int cost = rand();
                addEdge(num[i][j], num[i + 1][j], cost, {i * 2 + 1, j * 2});
            }

            if (j + 1 < n) {
                int cost = rand();
                addEdge(num[i][j], num[i][j + 1], cost, {i * 2, j * 2 + 1}); 
            }
        }
    }

    sort(edge_list.begin(), edge_list.end());
    for (auto &itr : edge_list) {
        if (not copaci.sameUnion(itr.getVertices())) {
            copaci.Union(itr.getVertices());
            itr.apm_selected = true;
            // cerr << "!";
        }
        // for (int i = 0; i <= n * n; i += 1) {
        //     cerr << copaci.father[i] << ' ';
        // }
        // cerr << "\n\n";
    }

    for (int i = 0; i < N; i += 1) {
        for (int j = 0; j < N; j += 1) {
            final_matrix[i][j] = (i % 2 == 0 and j % 2 == 0) ? ('0') : ('1');
        }
    }

    // for (int i = 0; i < N; i += 1) {
    //     for (int j = 0; j < N; j += 1) {
    //         cerr << final_matrix[i][j];
    //     }
    //     cerr << '\n';
    // }

    // for (auto itr : edge_list) {
    //     cerr << itr.a << '\t' << itr.b << '\t' << itr.c << '\t' << itr.apm_selected << '\n';
    // }

    for (auto itr : edge_list) {
        if (itr.apm_selected) {
            auto position = itr.getPosition();    
            final_matrix[position.first][position.second] = '0';
        }
    }

    ofstream fout("hack.out");
    fout << "50 50 1 1\n";

    for (int i = 0; i < N; i += 1) {
        for (int j = 0; j < N; j += 1) {
            fout << final_matrix[i][j];
        }
        fout << '\n';
    }


    return 0;
}