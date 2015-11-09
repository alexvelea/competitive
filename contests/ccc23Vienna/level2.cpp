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
    int position, finish, time, finishTime;
    Car() {
        position = finish = time = -1;
        finishTime = 0;
    }

    Car(int _position, int _finish, int _time) {
        position = _position;
        finish = _finish;
        time = _time;
        finishTime = 0;
    }
} cars[kMaxN];

int rez[kMaxN];
priority_queue<pair<int, int> > pq;

void solve() {
    int time = -pq.top().first;
    unordered_map<int, bool> here, next;
    vector<int> carsInside, nextCars, waitList;

    while (int(carsInside.size()) or int(pq.size())) {

        for (auto itr : carsInside) {
            Car car = cars[itr];
            if (car.position == car.finish) {
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

int main() {
    freopen("data.txt", "r", stdin);
    
    int n, m;
    scanf("%d\n%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d,%d,%d", &a, &b, &c);

        cars[i] = Car(a, b, c);
        pq.push({-c, i});
    }
    solve();

    for (int i = 1; i <= m; ++i) {
        fout << cars[i].finishTime << ',';
    }
    return 0;
}
