#include <fstream>
#include <cstdlib>
using namespace std;

ifstream fin("semne.in");
ofstream fout("semne.out");
const int MAX_N = 55000;

int sir[MAX_N];
int poz[MAX_N], neg[MAX_N];
char semn[MAX_N];
int N;
long long sum, S;

void read_input();
void solve();
void write_output();

int main()
{
    read_input();
    solve();
    write_output();
}

void read_input() {
    sum = 0;
    fin >> N >> S;
    for (int i = 1; i <= N; ++i) {
        fin >> sir[i];
        if (sum > S) {
            semn[i] = '-';
            neg[++neg[0]] = i;
            sum -= sir[i];
        } else {
            semn[i] = '+';
            poz[++poz[0]] = i;
            sum += sir[i];
        }
    }
}

void solve() {
    srand(time(0));
    while (sum != S) {
        if (sum < S) {
            int pos = rand() % neg[0] + 1;
            sum += 2 * sir[neg[pos]];
            semn[neg[pos]] = '+';
            poz[++poz[0]] = neg[pos];
            neg[pos] = neg[neg[0]];
            --neg[0];
        } else {
            int pos = rand() % poz[0] + 1;
            sum -= 2 * sir[poz[pos]];
            semn[poz[pos]] = '-';
            neg[++neg[0]] = poz[pos];
            poz[pos] = poz[poz[0]];
            --poz[0];
        }
    }
}

void write_output() {
    for (int i = 1; i <= N; ++i) {
        fout << semn[i];
    }
}
