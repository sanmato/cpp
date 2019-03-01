#ifndef COLLECTION_H
#define COLLECTION_H

#include <stdio.h>
#include <iostream>
#include <cstring>

//#define __DEBUG__

template< typename ItemType >
struct Collection
{
    enum{ NULL_ITEM = 0, EMPTY = -1, DEFAULT_CAPACITY = 512 };

    typedef bool( *Condition )( const ItemType& item );
    typedef void( *LayoutFunction )( const ItemType& item );
    typedef bool( *SlicingPredicate )( unsigned long itemPos, unsigned long starting, unsigned long ending);

    ItemType items[ DEFAULT_CAPACITY ];

    size_t first;
    size_t last;
    ItemType* current;

    unsigned long count;

    bool initialized;

    //PRIVATE HELPERS FUNCTIONS

    static bool all_items( const ItemType& lhs );
    static void simple_layout( const ItemType& item );
    void add_item( Collection<ItemType>& collection, const ItemType& item);
    Collection<ItemType>& remove_first( Collection<ItemType>& collection );
    Collection<ItemType>& remove_last( Collection<ItemType>& collection );
    Collection<ItemType>& remove_item( Collection<ItemType>& collection, unsigned long pos );
    void slice( Collection<ItemType>& collection, Collection<ItemType>& result, unsigned long starting,
                unsigned long ending, SlicingPredicate predicate);
    static bool outerOuterPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending);
    static bool innerInnerPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending);
    static bool innerOuterPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending);
    static bool outerInnerPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending);

    //INIT FAMILY FUNCTIONS

    void init( void );
    void init( const ItemType& item, size_t count );
    void init( const ItemType values[], size_t nbValues );
    void init( const Collection<ItemType>& otherCollection );

    //RELEASE&RESET FUNCTIONS

    void release( void );
    void reset( void );

    //ADD FAMILY FUNCTIONS

    Collection<ItemType>& add( const ItemType& item );
    Collection<ItemType>& add( const ItemType values[], size_t nbValues );
    Collection<ItemType>& add( const Collection<ItemType>& otherCollection );

    //REMOVE FAMILY FUNCTIONS

    Collection<ItemType>& removeFirst( void );
    Collection<ItemType>& removeLast( void );
    Collection<ItemType>& remove( const ItemType& item );
    Collection<ItemType>& remove( ItemType values[], size_t nbValues );
    Collection<ItemType>& remove( Collection<ItemType>& itemsToRemove );
    Collection<ItemType>& remove( Condition condition );

    //QUERY FAMILY FUNCTIONS

    size_t size( void ) const;
    size_t capacity( void ) const;
    bool isEmpty( void ) const;
    bool isFull( void ) const;
    long indexOf( const ItemType& item ) const;
    ItemType& itemAtPos( unsigned long pos );
    ItemType itemAtPos( unsigned long pos ) const;
    bool contain( const ItemType& item ) const;

    //ASSIGN A.K.A OPPERATOR "="

    Collection<ItemType>& assign( const Collection<ItemType>& rhs);

    //ITERATOR FAMILY FUNCTIONS

    ItemType* firstItem( void );
    ItemType* nextItem( void );

    //AGREGATE FAMILY FUNCTIONS

    Collection<ItemType> select( Condition condition = all_items);

    //SLICING FAMILY FUNCTIONS

    Collection<ItemType> outerSlice( unsigned long starting, unsigned long ending );
    Collection<ItemType> innerSlice( unsigned long starting, unsigned long ending );
    Collection<ItemType> innerOuterSlice( unsigned long starting, unsigned long ending );
    Collection<ItemType> outerInnerSlice( unsigned long starting, unsigned long ending );
    Collection<ItemType> outerTrimLeft( unsigned long starting );
    Collection<ItemType> innerTrimLeft( unsigned long starting );
    Collection<ItemType> innerOuterTrimLeft( unsigned long starting );
    Collection<ItemType> outerInnerTrimLeft( unsigned long starting );
    Collection<ItemType> outerTrimRight( unsigned long starting );
    Collection<ItemType> innerTrimRight( unsigned long starting );
    Collection<ItemType> innerOuterTrimRight( unsigned long starting );
    Collection<ItemType> outerInnerTrimRight( unsigned long starting );

    //DUMP FAMILY FUNCTION

    void dump( LayoutFunction itemLayout = simple_layout );

};

template< class ItemType >
bool Collection<ItemType>::all_items( const ItemType& lhs )
{
    return true;
}

template< class ItemType >
void Collection<ItemType>::simple_layout( const ItemType& item )
{
    std::cout << item;
}

//INIT FAMILY

template< class ItemType >
void Collection<ItemType>::init( void )
{
    memset( items, NULL_ITEM, sizeof( ItemType )* DEFAULT_CAPACITY);
    first = EMPTY;
    last = EMPTY;
    current = nullptr;
    count = 0;
    initialized = true;
}

template< class ItemType >
void Collection<ItemType>::init( const ItemType& item, size_t nb )
{
    #ifdef __DEBUG__
        assert( nb <= DEFAULT_CAPACITY );
    #endif // __DEBUG__

    memset( items, NULL_ITEM, sizeof( ItemType )* DEFAULT_CAPACITY );
    for( int idx = 0; idx < nb; idx++ ) items[ idx ] = item;
    first = EMPTY;
    last = nb - 1;
    current = nullptr;
    count = nb;
    initialized = true;
}

template< class ItemType >
void Collection<ItemType>::init( const ItemType values[], size_t nbValues )
{
    #ifdef __DEBUG__
        assert( nbValues <= DEFAULT_CAPACITY );
    #endif // __DEBUG__

    memcpy( items, values, nbValues * sizeof( ItemType ) );
    first = 0;
    current = nullptr;
    last = nbValues - 1;
    count = nbValues;
    initialized = true;
}

template< class ItemType >
void Collection<ItemType>::init( const Collection<ItemType>& otherCollection)
{
    #ifdef __DEBUG__
        assert( otherCollection.initialized );
    #endif // __DEBUG__

    memcpy( items, otherCollection.items, otherCollection.count * sizeof( ItemType ) );

    first = 0;
    current = nullptr;
    last = otherCollection.count - 1;
    count = otherCollection.count;
    initialized = true;
}

//RELEASE & RESET FAMILY FUNCTIONS

template< class ItemType >
void Collection<ItemType>::release( void )
{
    init();
}

template< class ItemType >
void Collection<ItemType>::reset( void )
{
    init();
}

//ADD FAMILY FUNCTIONS

template< class ItemType >
void Collection<ItemType>::add_item( Collection<ItemType>& collection, const ItemType& item )
{
    #ifdef __DEBUG__
        assert( collection.count < DEFAULT_CAPACITY );
    #endif // __DEBUG__

    unsigned long placeForNewItem = collection.count;
    collection.items[ placeForNewItem ] = item;

    if( collection.count == 0 )
    {
        //LA COLECCION ESTA VACIA
        collection.first = 0;
        collection.current = nullptr;
        collection.last = 0;
    }
    else
    {
        //YA HAY ITEMS
        collection.last++;
    }
    collection.count++;

    #ifdef __DEBUG__
        assert( ( collection.count == placeForNewItem + 1) && ( collection.count <= DEFAULT_CAPACITY) );
        assert( collection.last == collection.first + ( collection.count - 1) );
    #endif // __DEBUG__
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::add( const ItemType& item)
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    add_item( *this, item );
    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::add( const ItemType values[], size_t nbValues )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( ( count + nbValues ) <=DEFAULT_CAPACITY );
    #endif // __DEBUG__

    for( int index = 0; index < nbValues; index++)
    {
        add_item( *this, values[ index ] );
    }
    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::add( const Collection<ItemType>& otherCollection )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( ( count + otherCollection.count ) <=DEFAULT_CAPACITY );
    #endif // __DEBUG__

    for( int index = 0; index < otherCollection.count; index++ )
    {
        add_item( *this, otherCollection.items[ index ] );
    }
    return *this;
}

//REMOVE FAMILY FUNCTIONS

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove_first( Collection<ItemType>& collection )
{
    if( collection.count > 1 )
    {
        memmove( &( collection.items[ 0 ]), &( collection.items[ 1 ]), ( collection.count - 1) * sizeof( ItemType ) );
        collection.items[ last ] = ( ItemType ) NULL_ITEM;
        collection.last--;
    }
    else
    {
        //PRIMERO Y ULTIMO
        collection.items[ 0 ] = ( ItemType ) NULL_ITEM;
        collection.first = EMPTY;
        collection.last = EMPTY;
    }
    collection.count--;

    #ifdef __DEBUG__
        assert( collection.last == collection.first + ( collection.count - 1) );
    #endif // __DEBUG__

    return collection;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove_last( Collection<ItemType>& collection )
{
    #ifdef __DEBUG__
        assert( collection.initialized );
    #endif // __DEBUG__

    if( collection.count > 1 )
    {
        collection.items[ collection.count - 1 ] = ( ItemType ) NULL_ITEM;
        collection.last--;
    }
    else
    {
        collection.items[ 0 ] = ( ItemType ) 0;
        collection.first = EMPTY;
        collection.last = EMPTY;
    }
    collection.count--;
    #ifdef __DEBUG__
        assert( collection.last == collection.first + ( collection.count - 1) );
    #endif // __DEBUG__

    return collection;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove_item( Collection<ItemType>& collection, unsigned long pos )
{
    #ifdef __DEBUG__
        assert( collection.initialized );
        assert( ( pos >= 0 ) && ( pos < collection.count ) );
    #endif // __DEBUG__

    if( pos == 0)
    {
        remove_first( collection );
    }
    else if( pos == collection.count - 1 )
    {
        remove_last( collection );
    }
    else
    {
        //REMOVE OTHER
        memmove( &( collection.items[ pos ] ),
                 &( collection.items[ pos + 1 ] ),
                 ( ( collection.last - collection.first ) - pos ) * sizeof( ItemType ) );
        collection.last--;
        collection.count--;
    }

    #ifdef __DEBUG__
        assert( collection.last == collection.first + ( collection.count - 1) );
    #endif // __DEBUG__

    return collection;

}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::removeFirst( void )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    if( count != 0 ) __remove_first__( *this );
    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::removeLast( void )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    if( count != 0 ) remove_last( *this );
    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove( const ItemType& item)
{
    #ifdef __DEBUG__
        assert( initialized )
    #endif // __DEBUG__

    unsigned long itemPos = indexOf( item );
    if( itemPos != -1) remove_item( *this, itemPos );

    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove( ItemType values[], size_t nbValues )
{
    #ifdef __DEBUG__
        assert( values != 0 );
    #endif // __DEBUG__

    for( int index = 0; index < nbValues; index++ )
    {
        remove( values[ index ] );
    }

    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove( Collection<ItemType>& itemsToRemove )
{
    #ifdef __DEBUG__
        assert( itemsToRemove.initialized );
    #endif // __DEBUG__

    ItemType* current = itemsToRemove.firstItem();
    while( current )
    {
        remove( *current );
        current = itemsToRemove.nextItem();
    }

    return *this;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::remove( Condition condition )
{
    #ifdef __DEBUG__
        assert( condition != nullptr );
    #endif // __DEBUG__

    ItemType* current = firstItem();
    while( current )
    {
        if( condition( *current ) ) remove( *current );
        current = nextItem();
    }

    return *this;
}

//QUERY FAMILY FUNCTIONS

template< class ItemType >
size_t Collection<ItemType>::size( void ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    return count;
}

template< class ItemType >
size_t Collection<ItemType>::capacity( void ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    return DEFAULT_CAPACITY;
}

template< class ItemType >
bool Collection<ItemType>::isEmpty( void ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    return first == EMPTY;
}

template< class ItemType >
bool Collection<ItemType>::isFull( void ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    return count == DEFAULT_CAPACITY;
}

template< class ItemType >
long Collection<ItemType>::indexOf( const ItemType& item ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    int found = false;
    int pos = -1;

    for( int index = 0; ( index < count ) && !found; index++ )
    {
        if( memcmp( &items[ index ], &item, sizeof( ItemType ) ) == 0)
        {
            found = true;
            pos = index;
        }
    }

    return pos;
}

template< class ItemType >
ItemType& Collection<ItemType>::itemAtPos( unsigned long pos )
{
    #ifdef __DEBUG__
        assert( ( pos >= 0 ) && ( pos < count ) );
    #endif // __DEBUG__

    return items[ pos ];
}

template< class ItemType >
ItemType Collection<ItemType>::itemAtPos( unsigned long pos ) const
{
    #ifdef __DEBUG__
        assert( ( pos >= 0 ) && ( pos < count ) );
    #endif // __DEBUG

    return items[ pos ];
}

template< class ItemType >
bool Collection<ItemType>::contain( const ItemType& item ) const
{
    return indexOf( item ) != -1;
}

template< class ItemType >
Collection<ItemType>& Collection<ItemType>::assign( const Collection<ItemType>& rhs )
{
    release();
    init( rhs );
    return *this;
}

//ITERATOR FAMILY FUNCTIONS

template< class ItemType >
ItemType* Collection<ItemType>::firstItem( void )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    ItemType* result = nullptr;

    if( count != 0 )
    {
        result = &( items[ first ] );
        current = result;
    }

    return result;
}

template< class ItemType >
ItemType* Collection<ItemType>::nextItem( void )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    ItemType* next = ( ItemType* ) nullptr;
    ItemType* previous = current;

    if( current < ( items + ( count - 1) ) )
    {
        next = ++current;
    }
    else
    {
        current = previous;
    }

    return next;
}

//AGREGATE FAMILY FUNCTIONS

template< class ItemType >
Collection<ItemType> Collection<ItemType>::select( Condition condition )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    Collection result;
    result.init();

    #ifdef __DEBUG__
        assert( result.initialized );
    #endif // __DEBUG__

    ItemType* current = firstItem();
    while( current )
    {
        if( condition( *current ) ) result.add( *current );
        current = nextItem();
    }
    return result;
}

//SLICING FAMILY FUNCTIONS

template< class ItemType >
void Collection<ItemType>::slice( Collection<ItemType>& collection, Collection<ItemType>& result,
                                  unsigned long starting, unsigned long ending, SlicingPredicate predicate )
{
    #ifdef __DEBUG__
        assert( collection.initialized );
        assert( result.initialized );
        assert( ( starting >= 0 ) && ( starting <= collection.count - 1 ) );
        assert( ( ending >= 0 ) && ( ending <= collection.count - 1 ) );
    #endif // __DEBUG__

    if( ending < starting )
    {
        unsigned long temp = starting;
        starting = ending;
        ending = temp;
    }
    #ifdef __DEBUG__
        assert( starting <= ending  );
    #endif // __DEBUG__

    for( size_t pos = starting; pos < count; pos++ )
    {
        if( predicate( pos, starting, ending ) ) result.add( items[ pos ] );
    }
}

template< class ItemType >
bool Collection<ItemType>::outerOuterPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending )
{
    return( itemPos >= starting ) && (itemPos <= ending );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerSlice( unsigned long starting, unsigned long ending )
{
    Collection result;
    result.init();
    slice( *this, result, starting, ending, outerOuterPredicate );
    return result;
}

template< class ItemType >
bool Collection<ItemType>::innerInnerPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending )
{
    return( itemPos > starting ) && (itemPos < ending );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerSlice( unsigned long starting, unsigned long ending )
{
    Collection result;
    result.init;
    *slice( *this, result, starting, ending, innerInnerPredicate() );
    return result;
}

template< class ItemType >
bool Collection<ItemType>::innerOuterPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending )
{
    return( itemPos > starting ) && ( itemPos <= ending );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerOuterSlice( unsigned long starting, unsigned long ending )
{
    Collection result;
    result.init;
    *slice( *this, result, starting, ending, innerOuterPredicate() );
    return result;
}

template< class ItemType >
bool Collection<ItemType>::outerInnerPredicate( unsigned long itemPos, unsigned long starting, unsigned long ending )
{
    return( itemPos >= starting ) && ( itemPos < ending );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerInnerSlice( unsigned long starting, unsigned long ending )
{
    Collection result;
    result.init();
    *slice( *this, result, starting, ending, outerInnerPredicate );
    return result;
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerTrimLeft( unsigned long starting )
{
    return outerSlice( starting, count - 1 );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerTrimLeft( unsigned long starting )
{
    return innerSlice( starting, count - 1 );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerOuterTrimLeft( unsigned long starting )
{
    return innerOuterSlice( starting, count - 1 );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerInnerTrimLeft( unsigned long starting )
{
    return outerInnerSlice( starting, count - 1 );
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerTrimRight( unsigned long starting )
{
    return outerSlice( 0, starting);
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerTrimRight( unsigned long starting )
{
    return innerSlice( 0, starting);
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::innerOuterTrimRight( unsigned long starting )
{
    return innerOuterSlice( 0, starting);
}

template< class ItemType >
Collection<ItemType> Collection<ItemType>::outerInnerTrimRight( unsigned long starting )
{
    return outerInnerSlice( 0, starting);
}

template< class ItemType >
void Collection<ItemType>::dump( LayoutFunction itemLayout )
{
    for( int idx = 0; idx < count; idx++ ) itemLayout( items[ idx ] );
}

#endif // COLLECTION_H
