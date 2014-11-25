#ifndef ARRAYLIST_INCLUDED
#define ARRAYLIST_INCLUDED

#include<stdlib.h>
#include<string.h>
#include"List.h"

typedef struct ArrayList{
    List super;
    unsigned long size;
    char* array;
} ArrayList;

inline static void* ArrayList_get( const List* list, const unsigned long i ){
    ArrayList* l = (ArrayList*) list;
    return l->array + i * l->size;
}

inline static void ArrayList_set( List* list, const void* elem, const unsigned long i ){
    ArrayList* l = (ArrayList*) list;
    unsigned long size = l->size;
    memcpy( l->array + i * size, elem, size );
}

inline static void ArrayList_destroy( List* list ){
    ArrayList* l = (ArrayList*) list;
    free( l->array );
    free( l );
}

static const ListI methods = {
    ArrayList_get,
    ArrayList_set,
    ArrayList_destroy
};

inline List* ArrayList_new( unsigned long length, unsigned long size ){
    List super = { length, &methods };
    ArrayList* self = malloc( sizeof( *self ) );
    memcpy( &self->super, &super, sizeof( super ) );
    self->size = size;
    unsigned long bytes = length * size * sizeof( *self->array );
    self->array = malloc( bytes );
    //zero out the array
    memset( self->array, 0, bytes );
    return &self->super;
}

#endif
