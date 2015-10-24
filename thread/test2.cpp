#include <thread>
#include <iostream>
#include <cstdlib>
using namespace std;

thread t1, t2;

void wait(double x = 1.0) {
    time_t t = clock();
    while ((clock() - t) < x * CLOCKS_PER_SEC);
    return ;
}

void show() {
    while (1) {
        cerr << "#";
        wait(0.2);
    }
}



struct SX {
    thread th;
    void init() {
        cerr << "Start SX\n";
        th = thread([](double x = 2.0) {
            time_t t = clock();
            while ((clock() - t) < x * CLOCKS_PER_SEC);
            return ;
        });
        th.join();
        cerr << "END SX\n";
    }
};

SX* sx;

int nr;

void w() {
//    thread t(show);
    cerr << "Start W\n";
    wait(2.5);
    ++nr;
    cerr << nr << '\n';
    cerr << "End W\n";
/*
    cerr << "!";
    cerr << "?!!?!?!" << sx->th.joinable() << '\n';
    sx->th.detach();
*/

//    thread t2;
//    swap(t, t2);
//    t2.join(); 
}
    
void f() {
    while (1) {
        thread t(w);
        t.detach();
        wait(0.5);
        t = thread();
    }
    return ;
}

int main() {
    f();
    return 0;
}
