#include <cstdlib>

int main() {
    system("g++ -std=c++0x -O2 -Wall main.cpp -o main -lm");
    system("./main");
    system("./eval");
}
