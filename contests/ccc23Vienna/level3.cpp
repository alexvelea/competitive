#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include <cstdio>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 5 + 1e5;

//ifstream fin("level2_1.in");
ofstream fout("data.txt");

struct Car {
    int position, startPosition, finishPosition, startTime, finishTime, requestedTime;
    Car() {
        startPosition = finishPosition = -1;
        requestedTime = -1;
    }

    Car(int _startPosition, int _finishPosition, int _requestedTime) {
        startPosition = _startPosition;
        finishPosition = _finishPosition;
        requestedTime = _requestedTime;
        startTime = 0;
        finishTime= -inf;
    }
} cars[kMaxN];

int n, m;
priority_queue<pair<int, int> > pq;

void solve() {
    int time = -pq.top().first;
    unordered_map<int, bool> here, next;
    vector<int> carsInside, nextCars, waitList;

    while (int(carsInside.size()) or int(pq.size())) {

        for (auto itr : carsInside) {
            Car car = cars[itr];
            if (car.position == car.finishPosition) {
                car.finishTime = time;
            } else {
                if (here[car.position + 1] == false) {
                    car.position += 1;
                }

                next[car.position] = true;
                nextCars.push_back(itr);
            }

            cars[itr] = car;
        }

        while (pq.size() and -pq.top().first == time) {
            waitList.push_back(pq.top().second);
            pq.pop();
        }

/*
        cerr << time << '\t' << waitList.size() << '\n';
        for (auto itr : carsInside) {
            cerr << itr << "\t";
        }
        cerr << "\n\n";
*/        

        for (int itr = 0; itr < int(waitList.size()); ++itr) {
            int index = waitList[itr];
            int pos = cars[index].position;
            if (here[pos] == false and here[pos - 1] == false) {
                next[pos] = true;
                nextCars.push_back(index);
                swap(waitList[itr], waitList[int(waitList.size()) - 1]);
                waitList.pop_back();
                --itr;
            }
        }

        here = next;
        next.clear();

        carsInside = nextCars;
        nextCars.clear();

        if (carsInside.size()) {
            ++time;
        } else if (pq.size()) {
            time = -pq.top().first;
        }
    }
    return ;
}

void insertCars() {
    while (pq.size()) {
        pq.pop();
    }

    for (int i = 1; i <= m; ++i) {
        cars[i].position = cars[i].startPosition;
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
    } else {
        for (int i = 1; i <= m; ++i) {
            if (cars[i].finishTime + 20 < cars[i].requestedTime) {
                cars[i].startTime += cars[i].requestedTime - cars[i].finishTime;
            } else if (cars[i].finishTime > cars[i].requestedTime) {
                cars[i].startTime -= cars[i].finishTime - cars[i].requestedTime - rand() % 10;
            }
        }
    }
    insertCars();
    solve();
    search();
}

int main() {
    freopen("level3_4.in", "r", stdin);
    
    scanf("%d\n%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d,%d,%d", &a, &b, &c);

        cars[i] = Car(a, b, c);
        pq.push({-c, i});
    }
    search();
    
    for (int i = 1; i <= m; ++i) {
        fout << cars[i].startTime << ',';
    }
    return 0;
}
