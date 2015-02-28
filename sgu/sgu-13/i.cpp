#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

    #define max_n 200
    int n;
    char T[max_n];

    bool letter ( char c )
    {
        int ok=0;
        if ( ( c-'a'>=0 ) && ( 'z'-c >=0 ) )
            ok=1;
        if ( ( c-'A'>=0 ) && ( 'Z'-c >=0 ) )
            ok=1;
        return ok;
    }

    bool symbol ( char c )
    {
        int ok=0;
        if ( ( c-'0' >=0 ) && ( c-'0'<=9 ) )
            ok=1;
        if ( ( c== '-' ) || (c=='_'))
            ok=1;
        if ( letter ( c ) )
            ok=1;
        return ok;
    }

    bool word ( int st, int dr )
    {
        if ( dr < st )
            return 0;
        int i,ok=1;
        for ( i=st; i<=dr; i++ )
            if ( !symbol(T[i]) )
                ok=0;
        return ok;
    }

    bool domain ( int st, int dr )
    {
        if ( dr < st )
            return 0;
        int ok=1,i;
        for ( i=st; i<=dr; i++ )
            if ( letter ( T[i] ) )
                ;
            else
                ok=0;
        if ( ( (dr-st+1) != 2 ) && ( (dr-st+1) != 3 ) )
            ok=0;
        return ok;
    }

    bool prefix ( int st, int dr )
    {
        if ( dr < st )
            return 0;
        int i;
        for ( i=dr; i>=st; i-- )
        {
            if ( T[i] == '.' )
            {
                if ( word( i+1,dr ) && prefix ( st, i-1 ) )
                    return 1;
                return 0;
            }
        }
        if ( word ( st,dr ) )
            return 1;
        return 0;
    }

    bool sufix ( int st, int dr )
    {
        if ( dr < st )
            return 0;
        int i;
        for ( i=dr; i>=st; i-- )
        {
            if ( T[i] == '.' )
            {
                if ( domain ( i+1,dr ) && prefix ( st, i-1 ) )
                    return 1;
                return 0;
            }
        }
        return 0;
    }


    bool solve ( int st, int dr )
    {
        int i;
        for ( i=st; i<=dr; i++ )
            if ( T[i] == '@' )
            {
                if ( prefix ( 0,i-1 ) && sufix (i+1, dr ) )
                    return 1;
                else
                    return 0;
            }
        return 0;
    }

int main()
{
    cin>>n;
    cin.getline(T,max_n);
    for ( ; n; n-- )
    {
        cin.getline(T,max_n);
        if ( solve ( 0, strlen(T)-1 ) )
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
