#include<assert.h>
#include<stdio.h>
#include"ArrayList.h"

#define L 100
#define N 50

typedef struct Entry{
    int number;
    char str[N];
} Entry;

int equals( Entry* a, Entry* b ){
    if( a->number != b->number ) return 0;
    unsigned long i;
    for( i = 0 ; i < N ; ++i ){
        if( a->str[i] != b->str[i] ) return 0;
    }
    return 1;
}

int main( int argc, const char* argv[] ){
    printf( "Constructing ArrayList...\n" );
    List* list = ArrayList_new( L, sizeof( Entry ) );
    unsigned long i;
    unsigned long len = list->length;
    printf( "Checking that entries are zeroed...\n" );
    for( i = 0 ; i < len ; ++i ){
        //check that contents are zeroed properly
        int e = *(int*)List_get( list, i );
        //printf( "Entry points to %d\n", e );
        assert( !e );
    }
    printf( "Adding entries...\n" );
    //add entries
    for( i = 0 ; i < len ; ++i ){
        Entry e = { i, {i} };
        List_set( list,  &e, i );
    }
    printf( "Checking entries...\n" );
    //check that entries are correct
    for( i = 0 ; i < len ; ++i ){
        Entry e =  *(Entry*) List_get( list, i );
        Entry expct = { i, {i} };
        assert( equals( &e, &expct ) );
    }

    printf( "Passed.\n" );

}
