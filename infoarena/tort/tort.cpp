#include <cstdio>
#include <iostream>
using namespace std;

#define max_l 100

struct nrmare{
	int nrcif,Cif[max_l];
	nrmare(){
		int i;
		for( i=0; i<max_l; ++i )
			Cif[i]=0;
		nrcif=0;
	}
	nrmare( int a ){
		int i=0;
		for( i=0; i<max_l; ++i )
			Cif[i]=0;
		nrcif=0;
		do{
			Cif[nrcif++]=a%10;
			a/=10;
		}while(a);
	}
 	void inm( int b ){
		int i,t1=0,t2=0;
		for( i=0; i<max_l; ++i ){
			t2=t1;
			t1 = (1LL*Cif[i]*b+t1)/10;
			Cif[i]=(1LL*Cif[i]*b+t2)%10;
			if( Cif[i] || t1 )
				nrcif=i+1;
		}
	}
	void inm( nrmare b ){
		int i,j;
 		nrmare c(0);
		for( i=0; i<nrcif; ++i ){
			for( j=0; j<b.nrcif; ++j )
				c.Cif[i+j]+=Cif[i]*b.Cif[j];
		}
		for( i=0; i<max_l; ++i ){
			if( c.Cif[i] ){
				nrcif=i+1;
				c.Cif[i+1]+=c.Cif[i]/10;
				Cif[i]=c.Cif[i]%10;
			}
		}
	}
	void sum ( nrmare b ){
		int i;
		for( i=0; i<max(nrcif,b.nrcif); ++i )
			Cif[i]+=b.Cif[i];
        for( i=0; i<max_l; ++i ){
			if( Cif[i] ){
				nrcif=i+1;
				Cif[i+1]+=Cif[i]/10;
				Cif[i]%=10;
			}
		}
	}
	void dif( nrmare b ){
		int i;
		for( i=0; i<max_l; ++i ){
			Cif[i]-=b.Cif[i];
			if( Cif[i]<0 ){
				Cif[i]+=10;
				Cif[i+1]--;
			}
            if( Cif[i] )
				nrcif=i+1;
		}
	}
	void afisare(){
		int i;
		for( i=nrcif-1; i>=0; --i )
			cout<<Cif[i]<<"";
		cout<<"\n";
	}
};

int main(){
	freopen("tort.in","r",stdin);
	freopen("tort.out","w",stdout);
	int a,b;
	cin>>a>>b;
 	nrmare q(a+1),w(b+1),e(a+1);
	e.inm(b+1);
	if( b&1 ){
		q.inm( (b+1)/2 );
		q.inm( b+2 );
	}else{
		q.inm( (b+2)/2 );
		q.inm( b+1 );
	}

	if( a&1 ){
		w.inm( (a+1)/2 );
		w.inm( a+2 );
	}else{
		w.inm( (a+2)/2 );
		w.inm( a+1 );
	}
	q.sum(w);
	q.dif(e);
	q.afisare();
	return 0;
}
