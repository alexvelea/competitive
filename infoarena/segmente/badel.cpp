#include <fstream>
// #include <iostream>
 
std::ifstream fin;
std::ofstream fout;
 
const int N_MAX = 1010;
const int INF = 2000000001;
 
struct segment
{
    int x1, y1;
    int x2, y2;
} h[N_MAX], v[N_MAX];
int hNum = 0, vNum = 0;
 
int hovMat[N_MAX][N_MAX];
int N;
int result;
 
inline int min(int a, int b) {
    return (a > b ? b : a);
}
inline int max(int a, int b) {
    return (a > b ? a : b);
}
inline int abs(int x) {
  return ( x < 0 ? (x * -1) : x );
}
 
void read_input();
void solve();
void write_output();
 
int main(int argc, char const *argv[]) {
    read_input();
    solve();
  write_output();
    return 0;
}
 
void read_input() {
    fin.open("segmente.in");
    fin >> N;
    int x1, y1, x2, y2;
    for (int i = 0; i < N; ++i) {
        fin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            v[vNum].x1 = x1;
            v[vNum].y1 = y1;
            v[vNum].x2 = x2;
            v[vNum].y2 = y2;
            ++vNum;
        } else {
            h[hNum].x1 = x1;
            h[hNum].y1 = y1;
            h[hNum].x2 = x2;
            h[hNum].y2 = y2;
            ++hNum;
        }
    } 
    fin.close();
}
 
void solve() {
  int d11, d12, d21, d22;
    for (int i = 0; i < hNum; ++i) {
        for (int j = 0; j < vNum; ++j) {
            if (v[j].y1 <= h[i].y1 && h[i].y1 <= v[j].y2 &&
                  h[i].x1 <= v[j].x1 && v[j].x1 <= h[i].x2) {
                hovMat[i][j] = 0;
      } else {
        d11 = abs(h[i].y1 - v[j].y1);
        d12 = abs(h[i].y1 - v[j].y2);
        d21 = abs(v[j].x1 - h[i].x1);
        d22 = abs(v[j].x1 - h[i].x2);
                hovMat[i][j] = max(min(d11, d12), min(d21, d22));
            }
        }
    }
 
  result = INF;
  int min1, min2;
  int d;
  if (hNum < vNum) {
    for (int i = 0; i < hNum - 1; ++i) {
      for (int ii = i + 1; ii < hNum; ++ii) {
        min1 = INF, min2 = INF;
        for (int j = 0; j < vNum; ++j) {
          d = max(hovMat[i][j], hovMat[ii][j]);
          if (d <= min1) {
            min2 = min1;
            min1 = d;
          } else if (d < min2) {
            min2 = d;
          }
        }
        if (result > min2) 
          result = min2;
      }
    }
  } else {
    for (int i = 0; i < vNum - 1; ++i) {
      for (int ii = i + 1; ii < vNum; ++ii) {
        min1 = INF, min2 = INF;
        for (int j = 0; j < hNum; ++j) {
          d = max(hovMat[j][i], hovMat[j][ii]);
          if (d < min1) {
            min2 = min1;
            min1 = d;
          } else if (d < min2) {
            min2 = d;
          }
        }
        if (result > min2)
          result = min2;
      }
    }
  }
}
 
void write_output() {
  fout.open("segmente.out");
  fout << result << '\n';
  fout.close();
}
