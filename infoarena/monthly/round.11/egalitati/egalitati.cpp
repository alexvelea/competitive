#include <cstring>

#include <fstream>
#include <iostream>


using namespace std;

	ifstream in("egalitati.in");
	ofstream out("egalitati.out");


char Text[100005];
int n,i;

int solve ( int start ){
	int ok=1;
	int count=0,i;
	for ( i=start; Text[i]!='.' && Text[i]!=';' ; i++ ){
		if ( Text[i] == '(' ){
			count++;
		}
		if ( Text[i] == ')' ){
			count--;
		}
		if ( Text[i] == '=' ){
			if ( count ){
				ok=0;
			}
		}
	}
	if ( count ){
		ok=0;
	}

	if ( ok ){
		out<<"1\n";
	}
	else{
		out<<"0\n";
	}
	return i+1;
}

int main(){
	in>>Text;
	n=strlen(Text);
	for ( i=0; i<n; i = solve ( i ) ) 
		;

	return 0;
}
