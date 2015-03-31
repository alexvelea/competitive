#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int kMaxN = 45, inf = 0x3f3f3f3f;


ifstream fin("zuzu.in");
ofstream fout("zuzu.out");

int mars[100][100][100];
bool viz[100][100][100];

int goX[6] = {+1, -1, 0, 0, 0, 0};
int goY[6] = {0, 0, +1, -1, 0, 0};
int goZ[6] = {0, 0, 0, 0, +1, -1};

struct Rectangle {
	int x[2], y[2], z[2], dir;
	static int exp;

	Rectangle() {
	}
	
	Rectangle(ifstream &fin) {
		double aux;
		fin >> aux; x[0] = aux * exp;
		fin >> aux; x[1] = aux * exp;
		if (x[0] > x[1]) swap(x[0], x[1]);
		fin >> aux; y[0] = aux * exp;
		fin >> aux; y[1] = aux * exp;
		if (y[0] > y[1]) swap(y[0], y[1]);
		fin >> aux; z[0] = aux * exp;
		fin >> aux; z[1] = aux * exp;
		if (z[0] > z[1]) swap(z[0], z[1]);
		fin >> dir;
	}

	void goDir() {
		x[0] += goX[dir] * exp;
		x[1] += goX[dir] * exp;
		y[0] += goY[dir] * exp;
		y[1] += goY[dir] * exp;
		z[0] += goZ[dir] * exp;
		z[1] += goZ[dir] * exp;
	}
} el[kMaxN];

int Rectangle::exp = 100000;

int main() {
	int n, t; fin >> n >> t;
	for (int i = 1; i <= n; ++i) {
		el[i] = Rectangle(fin);
	}

    double mx = 0.0;
	int where = 0;

	for (int T = 1; T <= t; ++T) {
		// make uniq;
        vector<int> uniqX, uniqY, uniqZ;
		uniqX.push_back(-inf);
		uniqX.push_back(+inf);
        uniqY.push_back(-inf);
		uniqY.push_back(+inf);   	
        uniqZ.push_back(-inf);
		uniqZ.push_back(+inf);   	

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				uniqX.push_back(el[i].x[j] + j);
				uniqY.push_back(el[i].y[j] + j);
				uniqZ.push_back(el[i].z[j] + j);
			}
		}

		sort(uniqX.begin(), uniqX.end()); uniqX.resize(unique(uniqX.begin(), uniqX.end()) - uniqX.begin());
		sort(uniqY.begin(), uniqY.end()); uniqY.resize(unique(uniqY.begin(), uniqY.end()) - uniqY.begin());
		sort(uniqZ.begin(), uniqZ.end()); uniqZ.resize(unique(uniqZ.begin(), uniqZ.end()) - uniqZ.begin());

		for (int i = 1; i <= n; ++i) {
			el[i].goDir();
		}
		
		for (int i = 0; i < 100; ++i) 
			for (int j = 0; j < 100; ++j)
				for (int k = 0; k < 100; ++k) {
					mars[i][j][k] = 0;
				}

		for (int i = 1; i <= n; ++i) {
			for (int s = 0; s < 8; ++s) {
				int a = s & 1, b = s & 2, c = s & 3;
				b = b != 0;
				c = c != 0;
				int bonus[2] = {+1, -1};

				mars[lower_bound(uniqX.begin(), uniqX.end(), el[i].x[a]) - uniqX.begin()]
					[lower_bound(uniqY.begin(), uniqY.end(), el[i].y[b]) - uniqY.begin()]
					[lower_bound(uniqZ.begin(), uniqZ.end(), el[i].z[c]) - uniqZ.begin()] += bonus[(a + b + c) % 2];
			}
		}
		for (int i = 1; i < 100; ++i) 
			for (int j = 1; j < 100; ++j) 
				for (int k = 1; k < 100; ++j) {
					viz[i][j][k] = false;
					int rez = 0;
					for (int s = 0; s < 8; ++s) {
 						int a = s & 1, b = s & 2, c = s & 3;
						b = b != 0;
						c = c != 0;
		 				int bonus[2] = {+1, -1};
						rez += mars[i - a][j - b][k - c] * bonus[(a + b + c) % 2];
					}
					mars[i][j][k] = rez;
 				}
		queue<tuple<int, int, int> > bf;
		for (int i = 1; i < 100; ++i)
			for (int j = 1; j < 100; ++j)
				for (int k = 1; k < 100; ++k) {
					if (viz[i][j][k] == false and mars[i][j][k]) {
						bf.push(make_tuple(i,j,k));
						viz[i][j][k] = true;
						double rez = 0.0;
						while (bf.size()) {
							int x, y, z;
							tie(x, y, z) = bf.front();
							rez += 1.0 * (uniqX[x + 1] - uniqX[x]) * (uniqY[y + 1] - uniqY[y]) * (uniqZ[z + 1] - uniqZ[z]);
							bf.pop();
                            for (int i = 0; i < 6; ++i) {
								int xn = x + goX[i], yn = y + goY[i], zn = z + goZ[i];
								if (viz[xn][yn][zn] == false and mars[xn][yn][zn] != 0) {
									viz[xn][yn][zn] = true;
									bf.push(make_tuple(xn, yn, zn));
								}
							}
						}
						if (rez > mx) {
							mx = rez;
							where = T;
						}
					}
				}
	}
 	mx /= 1.0 * Rectangle::exp * Rectangle::exp * Rectangle::exp;
	mx += 0.2;
	fout << int(mx) << '\n' << where << '\n';
	return 0;
}
