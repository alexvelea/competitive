#include <fstream>
#include <iostream>
using namespace std;

const int max_n = 2505;

ifstream in("adriatic.in");
ofstream out("adriatic.out");

int max_r[max_n], max_c[max_n], min_r[max_n], min_c[max_n];
int el[max_n][max_n], sum_u_r[max_n][max_n], sum_d_l[max_n][max_n];
int up_right[max_n][max_n], down_left[max_n][max_n];
int m;
const int n = 2500;
int r[max_n * max_n], c[max_n * max_n];

void get_max (int &a, int b) {
	if (a == -1) {
		a = b;
		return ;
	}
	if (b == -1)
		return ;
	if (a < b)
		a = b;
}

void get_min (int &a, int b) {
	if (a == -1) {
		a = b;
		return ;
	}
	if (b == -1)
		return ;
	if (a > b)
		a = b;

}

int main() {
	cin >> m;
	for (int i = 0; i <= n + 1; ++i)
		min_c[i] = max_c[i] = min_r[i] = max_r[i] = -1;
	for (int i = 1; i <= m; ++i) {
		cin >> r[i] >> c[i];
		get_min(min_c[r[i]], c[i]);
		get_max(max_r[c[i]], r[i]);
		get_max(max_c[r[i]], c[i]);
		get_min(min_r[c[i]], r[i]);
		el[r[i]][c[i]] ++;
	}
	for (int i = 2; i <= n + 1; ++i) {
 		get_min(min_c[i], min_c[i - 1]);
		get_min(min_r[i], min_r[i - 1]);
	}
	for (int i = n - 1; i >= 0; --i) {
		get_max(max_r[i], max_r[i + 1]);
		get_max(max_c[i], max_c[i + 1]);
	}
	for (int i = n; i >= 0; --i)
		for (int j = 1; j <= n; ++j)
			sum_d_l[i][j] = sum_d_l[i + 1][j] + sum_d_l[i][j - 1] + el[i][j] - sum_d_l[i + 1][j - 1];
	for (int i = n; i; --i) 
		for (int j = 1; j <= n; ++j) {
			if (sum_d_l[i][j] == 0)
				continue;
			int r, c;
			r = i;
			c = j;
			get_max(r, max_r[j + 1]);
			get_min(c, min_c[i - 1]);
			down_left[i][j] = sum_d_l[i][j] + down_left[r][c];
		}
	for (int i = 1; i <= n; ++i)
		for (int j = n; j >= 0; --j)
			sum_u_r[i][j] = sum_u_r[i - 1][j] + sum_u_r[i][j + 1] + el[i][j] - sum_u_r[i - 1][j + 1];
	for (int i = 1; i <= n; ++i)
		for (int j = n; j; --j) {
			if (sum_u_r[i][j] == 0)
				continue;
			int r, c;
			r = i;
			c = j;
			get_min(r, min_r[j - 1]);
			get_max(c, max_c[i + 1]);
			up_right[i][j] = sum_u_r[i][j] + up_right[r][c];
		}
	for (int i = 1; i <= m; ++i) {
		int rez = 0;
		rez += up_right[r[i]][c[i]];
		rez += down_left[r[i]][c[i]];
		rez += m;
		rez -= 3;
		cout << rez << '\n';
	}           
/*	for (int i = 1; i <= 8; ++i) {
		cerr << max_r[i] << '\t' << min_c[i] << '\n';
	}
	cerr << '\n';

	for (int i = 1; i <= 8; ++i, cerr << '\n')
		for (int j = 1; j <= 8; ++j)
			cerr << down_left[i][j] << ' ';
 	cerr << '\n';
	for (int i = 1; i <= 8; ++i, cerr << '\n')
		for (int j = 1; j <= 8; ++j)
			cerr << sum_d_l[i][j] << ' ';*/
	
	return 0;
}
