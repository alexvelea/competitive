#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include <cstdio>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 5 + 1e5;

//ifstream fin("level2_1.in");
ofstream fout("data.txt");

struct Road {
    int length;
    pair<int, int> father;
} road[kMaxN];

struct Car {
    pair<int, int> position, startPosition, finishPosition;
    int startTime, finishTime, requestedTime;
    bool finished;
    Car() {
        startPosition = finishPosition = {-1, -1};
        requestedTime = -1;
    }

    Car(pair<int, int> _startPosition, pair<int, int> _finishPosition) {
        startPosition = _startPosition;
        finishPosition = _finishPosition;
        finishTime = -inf;
    }
} cars[kMaxN];

int n, m;
priority_queue<pair<int, int> > pq;

pair<int, int> backPosition(pair<int, int> x) {
    if (x.first == 0) {
        return {x.first, x.second - 1};
    }
    return {x.first, x.second + 1};
}

pair<int, int> go(pair<int, int> x, int direction) {
    x.second += direction;
    return x;
}

map<pair<int, int>, bool> hasTrafficLight;

bool isRed(int time, pair<int, int> position) {
    if (hasTrafficLight[position]) {
        return ((time + 1) % 60) <= 30;
    }
    return false;
}

void solve() {
    int time = -pq.top().first;
    map<pair<int, int>, bool> here, next;
    vector<int> carsInside, nextCars, waitList;

    while (int(carsInside.size()) or int(pq.size()) or int(waitList.size())) {
        for (auto itr : carsInside) {
            Car car = cars[itr];
            if (car.position.first == car.startPosition.first) {
                // jos
                if (car.position.second == 1) {
                    // enter main road
                    pair<int, int> enterPos = road[car.position.first].father;
                    if (here[enterPos] == false and here[go(enterPos, -1)] == false and (not isRed(time, enterPos))) {
                        car.position = enterPos;
                    }
                } else if (here[go(car.position, -1)] == false) {
                    car.position = go(car.position, -1);
                }
            } else if (car.position.first == 0) {
                // dreapta
                if (road[car.finishPosition.first].father == car.position) {
                    pair<int, int> enterPos = car.finishPosition;
                    enterPos.second = +1;
                    if (here[enterPos] == false) {
                        car.position = enterPos;
                    }
                } else if (here[go(car.position, +1)] == false) {
                    //if ((not isRed(time, go(car.position, 0))) and (not isRed(time, go(car.position, +1))))
                    if ((not isRed(time, go(car.position, +1))))
                        car.position = go(car.position, +1);
                }
            } else if (car.position.first == car.finishPosition.first) {
                // sus
                if (car.position == car.finishPosition) {
                    car.finishTime = time;
                    car.finished = true;
                } else if (here[go(car.position, +1)] == false) {
                    car.position = go(car.position, +1);
                }
            } else {
                cerr << "Wrong!\n";
            }

            if (not car.finished) {
                nextCars.push_back(itr);
            }

            cars[itr] = car;
        }

        while (pq.size() and -pq.top().first == time) {
            waitList.push_back(pq.top().second);
            pq.pop();
        }

        for (int itr = 0; itr < int(waitList.size());) {
            int index = waitList[itr];
            if (here[go(cars[index].startPosition, +0)] == false and 
                here[go(cars[index].startPosition, -0)] == false and // -1, but no
                here[go(cars[index].startPosition, +1)] == false) { 
                nextCars.push_back(index);
                cars[index].position = cars[index].startPosition;

                swap(waitList[itr], waitList[int(waitList.size()) - 1]);
                waitList.pop_back();
            } else {
                itr += 1;
            }
        }

        here.clear();

        carsInside = nextCars;
        nextCars.clear();

        for (auto itr : carsInside) {
            if (here[cars[itr].position]) {
                cerr << "Wrong\n";
            }
            here[cars[itr].position] = true;
        }

        if (carsInside.size()) {
            ++time;
        } else if (pq.size()) {
            time = -pq.top().first;
        }
 /*
        cerr << time << '\t' << waitList.size() << '\n';
        for (auto itr : carsInside) {
            cerr << cars[itr].position.first << '\t' << cars[itr].position.second << '\n';
        }
        cerr << '\n';
*/ 
    }
    return ;
}

void insertCars() {
    while (pq.size()) {
        pq.pop();
    }

    for (int i = 1; i <= m; ++i) {
//      cars[i].position = cars[i].startPosition;
        cars[i].finished = false;

        pq.push({-cars[i].startTime, i});
    }
}

void search() {
    bool ok = true;
    for (int i = 1; i <= m; ++i) {
        if (abs(cars[i].finishTime - cars[i].requestedTime) <= 20 and 
            cars[i].finishTime <= cars[i].requestedTime) {
        } else {
            ok = false;
        }
    }

    if (ok) {
        return ;
    }
    
    if (cars[1].finishTime == -inf) {
        ;
    } else {
        int nrBad = 0;
        for (int i = 1; i <= m; ++i) {
            if (cars[i].finishTime + 20 < cars[i].requestedTime) {
                cars[i].startTime += cars[i].requestedTime - cars[i].finishTime + rand() % 1;
                nrBad += 1;
            } else if (cars[i].finishTime > cars[i].requestedTime) {
                cars[i].startTime -= cars[i].finishTime - cars[i].requestedTime - rand() % 1;
                nrBad += 1;
            } else {
//                cars[i].startTime += (rand() % 7) - 4;
            }
        }
        cerr << nrBad << '\n';
    }
    insertCars();
    solve();
    search();
}

int main() {
    freopen("level6_6.in", "r", stdin);
    scanf("%d", &road[0].length);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d,%d", &a, &b);
        road[i].length = a;
        road[i].father = {0, b};
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, c, A, B;
        scanf("%d,%d,%d,%d,%d", &A, &a, &B, &b, &c);

        cars[i] = Car({A, a}, {B, b});
        cars[i].startTime = c;
    }

    int k; scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
        int x; scanf("%d", &x);
        hasTrafficLight[{0, x}] = true;
    }

    insertCars();
    solve();
    
//    search();
    
    for (int i = 1; i <= m; ++i) {
        fout << cars[i].finishTime << ',';
    }
    return 0;
}
