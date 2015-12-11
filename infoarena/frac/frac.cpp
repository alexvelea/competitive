#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

long long p,n,cn,target,rez,i;
vector<long long> Desc;

long long get_frac( long long f ){
	long long rez=0,nr;
	int i,j;
	for( i=1; i<(1<<Desc.size()); ++i ){
		nr=-1;
		for( j=0; j< int(Desc.size()); ++j ){
			if( i&(1<<j) )
				nr*=-1LL*Desc[j];
		}
 		rez+=1LL*f/nr;
	}
	return f-rez;
}

int main(){
	freopen("frac.in","r",stdin);
	freopen("frac.out","w",stdout);
	cin>>n>>target;
	cn=n;
	for( i=2; 1LL*i*i<=cn; ++i ){
		if( cn%i==0 ){
			Desc.push_back(i);
			while( cn%i == 0 )
				cn/=i;
		}
	}
	if( cn!=1 )
		Desc.push_back(cn);
	// cautam binar
	long long p=1LL<<62;
	for( ; p>0; p>>=1 ){
		if( get_frac( rez+p ) >= target )
			;
		else
			rez+=p;
	}
	rez++;
	cout<<rez<<"\n";
	return 0;
}
