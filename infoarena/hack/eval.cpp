#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#define PII pair<int, int>
#define VI vector<int>
const int STEPS = 1;
 
const int dx[5] = {0, 0, 1, -1};
const int dy[5] = {1, -1, 0, 0};
 
void message(int points, string mess) {
    cout << points << "\n";
    cerr << mess << "\n";
    exit(0);
}
 
int getDistance(vector<string> &A, PII start) {
    int n = A.size(), m = A[0].size();
    int COUNTER = 0;
 
    queue<PII> Q;
    vector<VI> d(n, vector<int> (m, n * m));
    d[start.first][start.second] = 0;
    Q.push(start);
     
    while(!Q.empty()) {
        PII node = Q.front();
        Q.pop();
         
        COUNTER++;
 
        for(int dir = 0; dir < 4; ++dir) {
            int newX = node.first + dx[dir];
            int newY = node.second + dy[dir];
            if(newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            int cost = 0;
            if(A[node.first][node.second] != A[newX][newY]) 
                cost = 1;
             
            if(d[node.first][node.second] + cost < d[newX][newY]) {
                d[newX][newY] = d[node.first][node.second] + cost;
                Q.push({newX, newY});
            }
        }
    }
 
    return COUNTER;
}
 
int main() {
     
    ifstream cin("hack.out");
 
    int n, m, startX, startY; 
     
    if(!(cin >> n >> m >> startX >> startY))
        message(0, "Fisier de iesire incomplet");
 
    if(startX < 1 || startX > n || startY < 1 || startY > m)
        message(0, "Incorect.\n");
 
    vector<string> A(n);
 
    for(int i = 0; i < n; ++i) {
        if(!(cin >> A[i]))
            message(0, "Fisier de iesire incomplet.\n");
        if((int) A[i].size() < m)
            message(0, "Fisier de iesire incomplet.\n");
    }
     
    int ans = getDistance(A, {startX - 1, startY - 1});
 
    if(ans >= STEPS)
        message(100, to_string(ans) + " pasi.");
 
    message(0, "Prea putini pasi :(.");
}
