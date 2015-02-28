//////
// Alex Velea
// 9 mai 2013
/////
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("showroom.in");
ofstream out("showroom.out");

const int max_n = 505, Mod = 9001, max_m = max_n * 105, buffer_size = max_n*40*100;
const int hash1 = 900000011, Sigma = 77;

#define fi first
#define se second
#define mp make_pair

int Fact[max_m];
char buffer[buffer_size];
int ind_act;

int n, a ,r, k;
int st, dr, i, j;

vector< pair<int, int> > Cars;
int Father[max_n], Number_of_cars[max_n];

int pow (int , int);
void make_comb ();
int get_char_number (char);

void get_min (int &a, int b){
	if (a>b)
		a=b;
}

int get_father(int nod){
	if (Father[nod] != nod)
		Father[nod] = get_father(Father[nod]);
	return Father[nod];
}

void set_father(int nod, int target){
	if (nod == Father[nod])
		;
	else
		set_father(Father[nod], target);
	Father[nod] = target;
}

int comb (int n, int k){
	int rez = 1, nr =0;
	nr += n/Mod;
	nr -= k/Mod;
	nr -= (n-k)/Mod;
	if (nr)
		return 0;
	rez *= Fact[n];
	rez = (1LL * rez * pow(Fact[k], Mod-2)) % Mod;
	rez = (1LL * rez * pow(Fact[n-k], Mod-2)) % Mod;
	return rez;
}


int main(){
	make_comb();
    in >> n >> a >> r >> k;
	in.read(buffer, buffer_size);
	ind_act = 1; // trecem peste \n de la finalul primei linii
	int h1;
	for (i=1; i<=n; ++i, ++ind_act){
		while (buffer[ind_act] != '\n'){
			while (buffer[ind_act] == ' ')
				++ind_act;
 			h1 = 0;
			while (!((buffer[ind_act] == ' ') || (buffer[ind_act] == '\n'))){
				h1 = (1LL*h1*Sigma + get_char_number(buffer[ind_act])) % hash1;
				++ind_act;
			}
			Cars.push_back (mp(h1,i));
		}
	}
	sort (Cars.begin(), Cars.end());
	for (i=1; i<=n; ++i){
		Father[i] = i;
	}
 	for (st=0; st<int(Cars.size()); ){
		dr = st;
		while (dr<int(Cars.size()) && Cars[st].fi == Cars[dr].fi)
			++dr;
		int target = n+1;
 		for (i=st; i<dr; ++i)
			get_min (target, get_father(Cars[i].se));
		for ( ; st<dr; ++st)
			set_father(Cars[st].se, target);
	}
	int nr_dealers = 0;
	for (i=1; i<=n; ++i){
		if (Father[i] == i)
			nr_dealers++;
	}
    for (st=0; st<int(Cars.size()); ){
		dr = st;
		while (dr<int(Cars.size()) && Cars[st].fi == Cars[dr].fi)
			++dr;
		Number_of_cars[get_father(Cars[st].se)]++;
		st = dr;
	}
	int number_of_buy = 1;
	a %= k;
	r %= k;
 	for (i=1; i<=n; ++i){
		if (i == Father[i]){
			if (Number_of_cars[i] >= a){
 				number_of_buy *= comb(Number_of_cars[i], a);
				number_of_buy %= Mod;
			}
			a += r;
			a -= k;
			if (a<0)
				a+=k;
		}
	}
 	out << nr_dealers << "\n" << number_of_buy << "\n";
	return 0;
}

int get_char_number (char c){
	if (c >= '0' && c <= '9')
		return c-'0'+1;
	if (c >= 'a' && c <= 'z')
		return c-'a'+10+1;
	return c-'A'+26+10+1;
}

int pow (int n, int p){
	int rez = 1;
	while (p){
		if (p&1)
			rez = (1LL * rez * n) % Mod;
		n = (1LL * n * n) % Mod;
		p >>= 1;
	}
	return rez;
}
void make_comb(){
	Fact[0] = 1;
	for (i=1; i<max_m; ++i)
		if (i%Mod)
			Fact[i] = (1LL * i * Fact[i-1]) % Mod;
		else
			Fact[i] = (1LL * i / Mod * Fact[i-1]) % Mod;
}
