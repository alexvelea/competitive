#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

    #define max_n 200005
    unsigned int T[max_n],q,a,r,k,n,i;

    unsigned int invers ( unsigned int nr ){
        int rez=0,i;
        for ( i=30; i>=0 && nr; i-- ){
            if ( nr & 1 ){
                rez|=(1<<i);
            }
            nr>>=1;
        }
        return rez;
    }


#define MaxChar 1000000
#define verf ((++CharC == MaxChar )?( cin.read(CharBuff,MaxChar),CharC=0):(1))

    long CharC=MaxChar-1;
    char CharBuff[MaxChar];

	void cit ( unsigned int &a )
	{
	    for ( ; CharBuff[CharC]<'0' || CharBuff[CharC]>'9'; verf )
	        ;
	    for ( a=0 ; CharBuff[CharC]>='0' && CharBuff[CharC]<='9'; a*=10, a+=( CharBuff[CharC]-'0' ), verf )
	        ;
	}


int main(){
        freopen ("rk.in","r",stdin);
        freopen ("rk.out","w",stdout);
	verf;

    cit(n);
    for ( i=1; i<=n; i++ ){
        cit(a);
        T[i]=invers(a);
    }
    T[++n]=(unsigned int)(-1+(1<<32));
    sort ( T+1, T+n+1 );
    cit(q);
    for ( ; q; q-- ){
        cit(a);
        cit(k);
        if ( k == 0 ){
            cout<<n-1<<"\n";
            continue;
        }
        r=invers(a);
        unsigned int ind=(1<<23);
        unsigned int rez1=0;
        if ( r !=0 ){
            for ( ; ind; ind>>=1 ){
                if ( ( ind+rez1 <= n ) && ( T[ind+rez1] <= ( r-1 ) ) )
                    rez1+=ind;
            }
        }
        if ( r!=0 ){
            if ( T[rez1] == r-1 )
                rez1++;
        }
        r+=(1<<(30-k+1));
        r--;
        unsigned int rez2=0;
        ind=(1<<23);
        for ( ; ind; ind>>=1 ){
            if ( ( ind+rez2<=n ) && ( T[ind+rez2] <= r ) )
                rez2+=ind;
        }
        cout<<rez2-rez1<<"\n";
    }
    return 0;
}
