#include<cstdio>
#include<vector>
#include<iostream>
#include<set>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

struct aa{
	int a,b;
	bool operator < ( const aa right ) const{
		return a < right.a;
	}
	aa(){
		a=b=0;
	}
} ;
set<int> S;
set<aa>SE;

int main(){
	aa act;
	act.a=1;
	act.b=2;
	SE.insert(act);
	act.b=3;
	SE.insert(act);
	FORIT( it, SE ){
		cout<<it->b<<"@\n";
	}


	S.insert(1);
	S.insert(2);
	S.insert(3);
	S.insert(5);
	S.insert(7);
	cout<<*S.lower_bound(6)<<"\n";
	return 0;
}
