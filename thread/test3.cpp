#include <iostream>
#include <thread>
using namespace std;

int rez[3];

void write(int x) {
    system("./sort");
    return ;
}

int main() {
    thread a, b;

    a = thread(write, 0);
//  a.detach();
    this_thread::sleep_for(chrono::milliseconds(int((1 + 1.05) * 1e3)));
    exit(0); 
//    a.join();
    return 0;

    write(2);
    cerr << rez[0] << '\t' << rez[1] << '\t' << rez[2] << '\n';
    return 0;
}
