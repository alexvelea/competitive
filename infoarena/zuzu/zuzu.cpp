//Problem zuzu from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 45, kExp = 100000;

ifstream in("zuzu.in");
ofstream out("zuzu.out");

class Rectangle {
  public:
	Rectangle();
	Rectangle(vector<int> &argv);
	void moveDir();
	void insertUniq();
	static void makeUniq();
	static void clearUniq();

	void addMars();
	static double solve();
  private:
  	static vector<vector<vector<int> > > mars;
	static vector<int> uniq[3];
	int static dir[3][6];

	int mDir;
	vector<int> mCoord[3];
};

// empty definition
vector<vector<vector<int> > > Rectangle::mars;
vector<int> Rectangle::uniq[3];
// precomputed direction array
int Rectangle::dir[3][6] = 	{{+1, -1, +0, +0, +0, +0}, {+0, +0, +1, -1, +0, +0}, {+0, +0, +0, +0, +1, -1}};

Rectangle::Rectangle() {}
Rectangle::Rectangle(vector<int> &argv) {	
	for (int itr = 0; itr < 3; ++itr) {
		mCoord[itr].resize(2);
		mCoord[itr][itr] = argv[itr];
		mCoord[itr][itr] = argv[itr + 3];
		sort(mCoord[itr].begin(), mCoord[itr].end());
		mCoord[itr][0]--;
	}
	
	mDir = argv[6];
}

void Rectangle::moveDir() {
	for (int itr = 0; itr < 3; ++itr) {
		for (int ind = 0; ind < 2; ++ind) {
			mCoord[itr][ind] += dir[itr][ind];
		}
	}
}

void Rectangle::clearUniq() {
	for (int itr = 0; itr < 3; ++itr) {
		uniq[itr].clear();
	}
}

void Rectangle::insertUniq() {
	for (int itr = 0; itr < 3; ++itr) {
 		uniq[itr].insert(uniq[itr].begin(), mCoord[itr].begin(), mCoord[itr].end());
	}
}

void Rectangle::makeUniq() {
    for (int itr = 0; itr < 3; ++itr) {
		sort(uniq[itr].begin(), uniq[itr].end());
		uniq[itr].resize(unique(uniq[itr].begin(), uniq[itr].end()) - uniq[itr].begin());
    }
	mars.resize(uniq[0].size());
	for (int i = 0; i < int(uniq[0].size()); ++i) {
		mars[i].resize(uniq[1].size());
    	for (int j = 0; j < int(uniq[1].size()); ++j) {
			mars[i][j].resize(uniq[2].size());
		}
	}
}

void Rectangle::addMars() {
	for (int st = 0; st < 8; ++st) {
		int ind[3] = {(st & 1) != 0, (st & 2) != 0, (st & 4) != 0};
 		mars[mCoord[0][ind[0]]][mCoord[1][ind[1]]][mCoord[2][ind[2]]] += ((ind[0] + ind[1] + ind[2]) & 1) ? (+1) : (-1);
	}
}

double Rectangle::solve() {
	int n = mars.size(), m = mars[0].size(), h = mars[0][0].size();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < h; ++k) {
				for (int st = 1; st < 8; ++st) {
					int minus[4] = {(st & 1) != 0, (st & 2) != 0, (st & 4) != 0, 0};
					if ((minus[0] + minus[1] + minus[2]) & 1) {
						minus[3] = +1;
					} else {
						minus[3] = -1;
					}
     				if (i - minus[0] >= 0 and j - minus[1] >= 0 and k - minus[2] >= 0)
	 					mars[i][j][k] += minus[3] * mars[i - minus[0]][j - minus[1]][k - minus[2]];
				}
			} 
		}
	}

 	bool viz[n][m][h];
 	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < h; ++k) {   
				viz[i][j][k] = false;
				if (mars[i][j][k] != 0)
					mars[i][j][k] = 1;
			}
		}
	}

	vector<tuple<int, int, int> > 

	return 0.0;
}

int main() {
	int n, t; in >> n >> t;
	vector<Rectangle> Dreptunghi(n);
	for (int i = 0; i < n; ++i) {
		vector<int> argv(7);
		for (int itr = 0; itr < 6; ++itr) {
			double el; in >> el;
			argv[itr] = int(1.0 * el * kExp + 0.5);
		}
		in >> argv[6];
		Dreptunghi[i] = Rectangle(argv);
	}
	
	while (t--) {
		for (int i = 0; i < n; ++i) {
			Dreptunghi[i].insertUniq();
		}
	}
	return 0;
}
