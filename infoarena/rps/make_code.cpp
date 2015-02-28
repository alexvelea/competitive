#include <fstream>
#include <iostream>
using namespace std;

int cod, Sigma=301, MOD=666013;
char c;

int main(){
	freopen("rps.out","r",stdin);
 	while( scanf("%c", &c ) == 1 ){
		cod = cod*Sigma;
		cod += c;
		cod %= MOD;
	}
	cerr<<cod<<"\n";
	return 0;
}
