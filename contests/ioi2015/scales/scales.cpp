#include "scales.h"

#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int btNr, btEl[6], btVis[6];
int btPos[6][720];
vector<int> btState[720];

void bt(int step) {
    if (step == 6) {
        for (int i = 0; i < 6; ++i) {
            btPos[btEl[i]][btNr] = i;
            btState[btNr].push_back(btEl[i]);
        }
        btNr++;
    } else {
        for (int i = 0; i < 6; ++i) {
            if (not btVis[i]) {
                btVis[i] = true;
                btEl[step] = i;
                bt(step + 1);
                btVis[i] = false;
            }
        }
    }
}

void init(int t) {
    btNr = 0;
    bt(0);
}

int remaining;
bool possible[720];

void sortByPos(vector<int> &el, int state) {
    for (int i = 0; i < int(el.size()); ++i) {
        for (int j = i + 1; j < int(el.size()); ++j) {
            if (btPos[el[i]][state] > btPos[el[j]][state]) {
                swap(el[i], el[j]);
            }
        }
    }
}

int get3Answer(vector<int> el, int left, int state) {
    sortByPos(el, state);
    return el[left];
}

int get4Answer(vector<int> el, int state) {
    int q = el[3];
    sortByPos(el, state);
    if (el[3] == q) {
        return el[0];
    }
    for (int i = 0; i < 3; ++i) {
        if (el[i] == q) {
            return el[i + 1];
        }
    }
    return 0;
}

int get3WorstCase(vector<int> el, int left) {
    vector<int> mx(6, 0);
    for (int i = 0; i < 720; ++i) {
        if (not possible[i]) {
            continue;
        }

        mx[get3Answer(el, left, i)]++;
    }
    
    int rez = 0;
    for (auto itr : mx) {
        rez = max(rez, itr);
    }
    return rez;
}

int get4WorstCase(vector<int> el) {
     vector<int> mx(6, 0);
    for (int i = 0; i < 720; ++i) {
        if (not possible[i]) {
            continue;
        }

        mx[get4Answer(el, i)]++;
    }
    
    int rez = 0;
    for (auto itr : mx) {
        rez = max(rez, itr);
    }
    return rez;     
}


struct Query {
    int type;
    vector<int> el;
    int cost;

    void execute() {
        if (type == 3) {
            int ans = getNextLightest(el);
            for (int i = 0; i < 720; ++i) {
                if (not possible[i]) {
                    continue;
                }

                if (get4Answer(el, i) != ans) {
                    remaining--;
                    possible[i] = false;
                }
            }
        } else {
            int ans;
            if (type == 0) {
                ans = getLightest(el);
            } else if (type == 1) {
                ans = getMedian(el);
            } else {
                ans = getHeaviest(el);
            }

            for (int i = 0; i < 720; ++i) {
                if (not possible[i]) {
                    continue;
                }

                if (get3Answer(el, type, i) != ans) {
                    remaining--;
                    possible[i] = false;
                }
            }
        }
    }
};

Query tryAll() {
    Query q; q.cost = inf;

    for (int a = 0; a < 6; ++a) {
        for (int b = a + 1; b < 6; ++b) {
            for (int c = b + 1; c < 6; ++c) {
                for (int d = 0; d < 6; ++d) {
                    if (d == a or d == b or d == c) {
                        continue;
                    }

                    int cost = get4WorstCase({a, b, c, d});
                    if (cost < q.cost) {
                        q.type = 3;
                        q.cost = cost;
                        q.el = {a, b, c, d};
                    }
                }
            }
        }
    } 

    for (int a = 0; a < 6; ++a) {
        for (int b = a + 1; b < 6; ++b) {
            for (int c = b + a; c < 6; ++c) {
                for (int left = 0; left < 3; ++left) {
                    int cost = get3WorstCase({a, b, c}, left);
                    if (cost < q.cost) {
                        q.type = left;
                        q.cost = cost;
                        q.el = {a, b, c};
                    }
                }
            }
        }
    }



    return q;
}

void orderCoins() {
    remaining = 720;
    for (int i = 0; i < 720; ++i) {
        possible[i] = true;
    }
   
    Query q;

    q.type = 0;
    q.el = {0, 1, 2};
    q.execute();

    q.type = 1;
    q.el = {3, 4, 5};
    q.execute();  

    while (remaining != 1) {
        tryAll().execute();
//        cerr << remaining << '\n';
    }

    for (int i = 0; i < 720; `++i) {
        if (possible[i]) {
            answer(btState[i]);
            return ;
        }
    }
}

