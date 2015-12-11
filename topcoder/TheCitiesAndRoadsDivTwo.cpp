#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

class TheCitiesAndRoadsDivTwo {
public:
	vector<int> Vertex[55],Nr;
	int Viz[55];

	int df( int nod ){
		Viz[nod]=1;
		int rez=0;
		FORIT( it, Vertex[nod] ){
			if( !Viz[*it] )
				rez+=df(*it);
		}
		return rez+1;
	}

    int find( vector <string> map )  {
		int l,i,n=map.size(),j;    
    	for( i=0; i<n; ++i )
			Viz[i]=0;
		for( i=0; i<n; ++i ){
			for( j=0; j<n; ++j )
				if( map[i][j]=='Y' )
					Vertex[i].push_back(j);
		}
		for( i=0; i<n; ++i ){
			if( !Viz[i] )
				Nr.push_back( df(i) );
		}       
		if( Nr.size() == 1 )
			return 1;
		int rez=0,act;
		for( i=0; i<Nr.size(); ++i ){
			for( j=i+1; j<Nr.size(); ++j ){
				act=1;
				for( l=0; l<Nr.size(); ++l ){
					if( l!=i && l!=j )
						act*=Nr[l]*Nr[l];
					else
						act*=Nr[l];
				}
				rez+=act;
			}
		}
		for( l=Nr.size()-2; l>0; --l )
			rez*=l;
		return rez;
	}
};



// Powered by FileEdit
// Powered by moj 4.17 [modified TZTester]
// Powered by CodeProcessor
