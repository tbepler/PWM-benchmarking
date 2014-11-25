#ifndef LIST_INCLUDED
#define LIST_INCLUDED

typedef struct ListI ListI;

typedef struct List {
    unsigned long length;
    const ListI* methods;
} List;

typedef struct ListI {
    void* (*get)( const List*, const unsigned long );
    void (*set)( List*, const void* elem, const unsigned long );
    void (*destroy)( List* );
} ListI;

inline void* List_get( const List* l, const unsigned long i ){
    return l->methods->get( l, i );
}

inline void List_set( List* l, const void* elem, const unsigned long i ){
    return l->methods->set( l, elem, i );
}

inline void List_destroy( List* l ){
    l->methods->destroy( l );
}

#endif
