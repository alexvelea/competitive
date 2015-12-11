//Problem #D from Codeforces MindcodingFinal1
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

bool finished;
int remaining = 17;

bool viz[20][20];

void computer_move() {
	int x, y;
	cin >> x >> y;
	if (viz[x][y]) {
		viz[x][y] = false;
		remaining--;
	}
	if (remaining == 0)
		finished = true;
	return ;
}

void init() {
 	int dx[] = {0, +1};
	int dy[] = {+1, 0};      
	int width[] = {5, 4, 3, 3, 2};
	int x[5], y[5], poz[5];
	for (int i = 0; i < 5; ++i) {
		int X, Y, POZ;
		bool ok = false;
		while (ok == false) {
 			X = rand() % 10 + 1;
			Y = rand() % 10 + 1;
			POZ = rand() % 2;    		

			ok = true;
			int nx = X, ny = Y;
			for (int d = 0; d < width[i]; ++d) {
				if (viz[nx][ny] == true)
					ok = false;
				if (nx > 10)
					ok = false;
				if (ny > 10)
					ok = false;

				nx += dx[POZ];
				ny += dy[POZ];
			}
		}
		x[i] = X;
		y[i] = Y;
		poz[i] = POZ;
 		
		for (int d = 0; d < width[i]; ++d) {
	    	viz[X][Y] = true;
			X += dx[POZ];
			Y += dy[POZ];
		}   	   	
	}
	for (int i = 4; i >= 0; --i)
		cout << x[i] << ' ' << y[i] << ' ' << poz[i] << '\n';
	cout.flush();
	return ;
}

bool hit[20][20], shot[20][20];

int nr_sank = 0;

int nr_shot = 0;

bool SHOT(int x, int y) {
	shot[x][y] = true;
	cout << x << ' ' << y << '\n';
	cout.flush();
	string response;
	cin >> response;
	if (response == "HIT") {
		hit[x][y] = true;
		nr_shot++;
		if (nr_shot == 17) {
			finished = true;
			return false; 
		}
	}
	if (response == "SANK") {
		hit[x][y] = true;
		nr_shot++;
		++nr_sank;
		if (nr_sank == 5 or nr_shot == 17) {
			finished = true;
			return false;
		}

		string aux;
		cin >> aux;
		if (aux == "aircraft")
			cin >> aux;
	}
	return true;
}

bool my_turn() {
	for (int x = 1; x <= 10; ++x)
		for (int y = 1; y <= 10; ++y)
			if (hit[x][y]) {
				int dx[4] = {+1, -1, 0, 0};
				int dy[4] = {0, 0, -1, +1};
	   			for (int d = 0; d < 4; ++d) {
		        	int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx > 0 and nx <= 10 and ny > 0 and ny <= 10 and shot[nx][ny] == false) {
						return SHOT(nx, ny);
					}
				}
			}

	while (1) {
/*		int x = rand() % 10 + 1;
		int y;
		y = rand() % 5;
        y *= 2;
		y ++;
		y += x % 2;*/
		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		if (shot[x][y] == false) {
			return SHOT(x, y);
		}
	}
}

int main() {
	srand(time(NULL));
	init();
	while (my_turn()) {
		if (finished)
			return 0;
		computer_move();
		if (finished)
			return 0;
	}
    return 0;
}

