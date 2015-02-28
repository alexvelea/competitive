#include<cstdio>
#include<iostream>
using namespace std;

int i,j,n,a,mx,Ap[10000],target,p;

int main(){
	freopen("lumanari.in","r",stdin);
 	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d", &a );
		Ap[a]++;
		if( mx<a )
			mx=a;
	}
	for( i=1; i<=n; ++i ){
		Ap[0]=0;
/*		for( j=mx; j>=0; --j )
			cerr<<Ap[j]<<" ";
		cerr<<"\n\n";*/
		// vedem daca putem merge mai departe
		target=i;
		p=mx;
		while( p>0 && target>Ap[p] ){
			target-=Ap[p];
			p--;
		}
		if( p==0 ){
			cerr<<i-1<<"\n";
			return 0;
		}
 		Ap[p]-=target;
		Ap[p-1]+=target;
		for( p++; p<=mx; ++p ){
			Ap[p-1]+=Ap[p];
			Ap[p]=0;
		}
 		
	}
	cerr<<n;
	return 0;
}
