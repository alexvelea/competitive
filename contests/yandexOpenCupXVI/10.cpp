#include <iostream>
#include <map>
#include <vector>
using namespace std;
map<pair<int, int>, bool> bad;
map<pair<int, int>, int> tileId;

int dx[7] = {-1, -1, 0, 0, 0, +1, +1};
int dy[7] = {0, +1, -1, 0, +1, -1, 0};
int H, W;
int nrOfTiles = 0;

const int kMaxTiles = 7000;
pair<int, int> posId[kMaxTiles];

int getId(int x, int y) {
    if (tileId[{x, y}] == 0) {
        tileId[{x, y}] = ++nrOfTiles;
        posId[nrOfTiles] = make_pair(x, y);
    }
    return tileId[{x, y}];
}

int getId(pair<int, int> x) {
    return getId(x.first, x.second);
}               

vector<int> vertex[kMaxTiles];

int cap[kMaxTiles][kMaxTiles], f[kMaxTiles][kMaxTiles];
pair<int, int> cityPos[10], catPos[150];
int cityHP[10], catMove[150];

void bt(int startX, int startY, int x, int y, int moves) {
    if (moves == 0) {
        cap[getId(startX, startY)][getId(x, y)] = 1; 
        return ; 
    }

    for (int i = 0; i < 7; ++i) {
        x += dx[i];
        y += dy[i];

        if (not bad[{x, y}] and x >= 0 and x < W and y >= 0 and y < H) {
            bt(startX, startY, x, y, moves - 1);
        }

        x -= dx[i];
        y -= dy[i];
    }
}

int viz[kMaxTiles];
int father[kMaxTiles];
int vizId = 0;

bool pumpFlow(int source, int sink) {
    ++vizId;
    vector<int> bfs;
    bfs.push_back(source);
    viz[source] = vizId;
    while (bfs.size() and viz[sink] != vizId) {
        int poz = rand() % bfs.size();
        int nod = bfs[poz];
        bfs[poz] = bfs.back();
        bfs.pop_back();

        for (auto itr : vertex[nod]) {
            if (viz[itr] != vizId and cap[nod][itr] - f[nod][itr] > 0) {
                viz[itr] = vizId;
                father[itr] = nod;
                bfs.push_back(itr);
            }
        }
    }

    if (viz[sink] != vizId) {
        return false;
    }

    for (int nod = sink; nod != source; nod = father[nod]) {
        f[father[nod]][nod]++;
    }
    return true;
}

int getFlow(int source, int sink) {
    int rez = 0;
    while (1) {
        int e = pumpFlow(source, sink);
        if (e == 0) {
            return rez;
        }
        rez += e;
    }
}

pair<int, int> rezPos[150];
int rezCity[150];

int main() {
    int nrCit, nrCat, nrM;
    cin >> W >> H;
    cin >> nrCit;
    for (int i = 1; i <= nrCit; ++i) {
        int x, y, p; cin >> x >> y >> p;
        cityPos[i] = make_pair(x, y);
        getId(x, y);
        cityHP[i] = p;
        bad[{x, y}] = true;
    }
    cin >> nrCat;
    for (int i = 1; i <= nrCat; ++i) {
        int x, y, v; cin >> x >> y >> v;
        catPos[i] = make_pair(x, y);
        catMove[i] = v;
    }
    cin >> nrM;
    for (int i = 1; i <= nrM; ++i) {
        int x, y; cin >> x >> y;
        bad[{x, y}] = true;
    }

    for (int i = 1; i <= nrCit; ++i) {
        for (int a = 0; a < 7; ++a) {
            for (int b = 0; b < 7; ++b) {
                int x = cityPos[i].first;
                int y = cityPos[i].second;
                x += dx[a] + dx[b];
                y += dy[a] + dy[b];
                if (not bad[{x, y}] and x >= 0 and x < W and y >= 0 and y < H) {
                    cap[getId(x, y)][getId(cityPos[i].first, cityPos[i].second)] = 1;
                }
            }
        }
    }
    
    for (int i = 1; i <= nrCat; ++i) {
        bt(catPos[i].first, catPos[i].second, catPos[i].first, catPos[i].second, catMove[i] - 1);
    }

    int source = nrOfTiles + 1;
    int sink = nrOfTiles + 2;
    posId[nrOfTiles + 1] = {-1, -1};
    posId[nrOfTiles + 2] = {-2, -2};
    nrOfTiles += 2;

    for (int i = 1; i <= nrCat; ++i) {
        cap[source][getId(catPos[i])] = 1;
    }

    for (int i = 1; i <= nrCit; ++i) {
        cap[getId(cityPos[i])][sink] = 1;
    }

/*    for (int i = 1; i <= nrOfTiles; ++i) {
        cout << posId[i].first << '|' << posId[i].second << "\t~";
        for (int j = 1; j <= nrOfTiles; ++j) {
            if (cap[i][j]) {
                cout << posId[j].first << "|" << posId[j].second << '\t';
            }
        }
        cout << '\n';
    }*/
                                
    for (int i = 1; i <= nrOfTiles; ++i) {
        for (int j = 1; j <= nrOfTiles; ++j) {
            if (cap[i][j]) {
                vertex[i].push_back(j);
                vertex[j].push_back(i);
            }
        }
    }

    int mx = 0;

    for (int i = 1; i <= nrCat; ++i) {
        rezPos[i] = catPos[i];
        rezCity[i] = 0;
    }

    for (int s = 1; s < (1 << nrCit); ++s) {
        int expected = 0;
        int nr = 0;
        for (int j = 0; j < nrCit; ++j) {
            if (s & (1 << j)) {
                expected += cityHP[j + 1];
                cap[getId(cityPos[j + 1])][sink] = cityHP[j + 1];
                nr++;
            } else {
                cap[getId(cityPos[j + 1])][sink] = 0;
            }
        }

        for (int i = 1; i <= nrOfTiles; ++i) {
            for (int j = 1; j <= nrOfTiles; ++j) {
                f[i][j] = 0;
            }
        }

        int v = getFlow(source, sink);
        if (v == expected) {
/*            for (int i = 1; i <= nrOfTiles; ++i) {
            cout << posId[i].first << '|' << posId[i].second << "\t~";
            for (int j = 1; j <= nrOfTiles; ++j) {
                if (f[i][j]) {
                    cout << posId[j].first << "|" << posId[j].second << '\t';
                }
            }
            cout << '\n';
            } */
            if (mx < nr) {
                mx = nr;
            for (int i = 1; i <= nrCat; ++i) {
                if (f[source][getId(catPos[i])] == false) {
                    rezPos[i] = catPos[i];
                    rezCity[i] = 0;
                } else {
                    for (auto itr : vertex[getId(catPos[i])]) {
                        if (f[getId(catPos[i])][itr]) {
                            for (auto itr2 : vertex[itr]) {
                                if (f[itr][itr2]) {
                                    rezPos[i] = posId[itr];
                                    for (int j = 1; j <= nrCit; ++j) {
                                        if (getId(cityPos[j]) == itr2) {
                                            rezCity[i] = j;
                                        }
                                    }
                                }
                            }

                            for (int j = 1; j <= nrCit; ++j) {
                                if (getId(cityPos[j]) == itr) {
                                    rezCity[i] = j;
                                    rezPos[i] = catPos[i];
                                }
                            }
                        }
                    }
                }
            }
            }
        }
    }
    cout << mx << '\n';
    for (int i = 1; i <= nrCat; ++i) {
        cout << rezPos[i].first << ' ' << rezPos[i].second << ' ' << rezCity[i] << '\n';
    }
    return 0;
}
