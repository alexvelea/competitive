#include <iostream>
#include <set>
#include <vector>
using namespace std;

set<int> S;
vector<int> V;

int main(){
	S.insert(10);
	S.insert(20);
	S.insert(30);
	set<int> :: iterator it;
	it = S.lower_bound(20);
	int i;
	V.reserve(50);
	for( i=0; i<405; ++i ){
		cerr<<i<<"\t"<<V.capacity()<<"\n";
		V.push_back(i);
	}
	return 0;
}
