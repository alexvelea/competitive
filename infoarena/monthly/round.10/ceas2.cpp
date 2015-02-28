#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

    #define max_n 100005

    int n,i,Rez[40];
    char a[max_n],b[max_n];

int main(){
    freopen ("ceas2.in","r",stdin);
    freopen ("ceas2.out","w",stdout);
    cin>>a>>b;
    n=strlen(a);
    for ( i=0; i<=30; i++ )
        Rez[i]=-1;
    for ( i=0; i<n; i++ ){
        if ( a[i]!=b[i] ){
            if ( Rez[a[i]-'a'] == -1 || Rez[a[i]-'a']==b[i]-'a' )
                Rez[ a[i]-'a' ] = b[i]-'a';
            else{
                cout<<"NU\n";
                return 0;
            }
        }
    }
    cout<<"DA\n";
    for ( i=0; i<=30; i++ ){
        if ( Rez[i]!=-1 ){
            cout<<char ( i+'a') <<" "<<char ( Rez[i]+'a' )<<"\n";
        }
    }
    return 0;
}
