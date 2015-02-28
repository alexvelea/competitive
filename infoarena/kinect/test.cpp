#include <cstdio>
#include <set>
using namespace std;

	set < pair<int,int> > Set;
	set < pair<int,int> > :: iterator it;
	int i; v

int main(){
	for ( i=1; i<=5; i++ ){
		Set.insert ( make_pair ( i, i+2 ) );
	}
	for ( it = Set.begin(); it!= Set.end(); it++ ){
		printf("%d %d\n", (*(it)).first, (*(it)).second);
	}
}

