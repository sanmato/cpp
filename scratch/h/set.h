#ifndef SET_H
#define SET_H

#include <stdio.h>

#ifndef static_collection_h
    #include "collection.h"
#endif // static_collection_h

template < class ItemType >
struct Set
{
    Collection<ItemType> rep;

    void init( void );
    void init( const ItemType values[], size_t nbValues );
    void init( Collection<ItemType>& collection );
    void init( Set<ItemType>& set );

    void release( void );
    void reset( void );

    Set<ItemType>& add( const ItemType& item );
    Set<ItemType>& add( const ItemType values[], size_t nbValues );
    Set<ItemType>& add( Collection<ItemType>& collection );
    Set<ItemType>& add( const Set<ItemType>& set );

    void intersect( Set<ItemType>& set, Set<ItemType>& result );
    Set<ItemType> intersect( Set<ItemType>& rhs);
    void setUnion( Set<ItemType>& set, Set<ItemType>& result );
    Set<ItemType> setUnion( Set<ItemType>& rhs );
    Set<ItemType> difference( const Set<ItemType>& rhs ) const;
    Set<ItemType> symetricDifference( const Set<ItemType>& rhs ) const;
    Collection<ItemType> asCollection( void ) const;

    size_t size( void ) const;
    bool isEmpty( void ) const;
    bool isFull( void ) const;
    bool subSet( const Set<ItemType>& rhs ) const;
    bool contain( const ItemType& item );

    Set<ItemType>& assign( const Set<ItemType>& rhs );

    ItemType* firstItem( void );
    ItemType* nextItem( void );

};

template< class ItemType >
void Set<ItemType>::init( void )
{
    return rep.init();
}

template< class ItemType >
void Set<ItemType>::init( const ItemType values[], size_t nbValues )
{
    rep.init();
    for( int i = 0; i < nbValues; i++ )
    {
        if( isEmpty() )
        {
            rep.add( values[ i ] );
        }
        else
        {
            if( !contain( values[ i ] ) )
            {
                rep.add( values[ i ] );
            }
        }
    }
}

template< class ItemType >
void Set<ItemType>::init( Collection<ItemType>& collection )
{
    rep.init();
    ItemType* item = collection.firstItem();
    while( item )
    {
        if( collection.isEmpty() )
        {
            rep.add( *item );
        }
        else
        {
            if( !contain( *item ) )
            {
                item = collection.nextItem();
            }
        }
    }
}

template< class ItemType >
void Set<ItemType>::init( Set<ItemType>& set )
{
    rep.init( set.rep );
}

template< class ItemType >
size_t Set<ItemType>::size( void ) const
{
    return rep.size();
}

template< class ItemType >
bool Set<ItemType>::isEmpty( void ) const
{
    return rep.isEmpty();
}

template< class ItemType >
bool Set<ItemType>::isFull( void ) const
{
    return rep.isFull();
}

template< class ItemType >
bool Set<ItemType>::contain( const ItemType& thisItem )
{
    bool result = false;
    ItemType* item = rep.firstItem();
    while( item && !result )
    {
        //if( *item == thisItem ) result = true;
        if( memcmp( item, &thisItem, sizeof( ItemType ) ) == 0 ) result = true;
        item = rep.nextItem();
    }
    return result;
}

template< class ItemType >
Set<ItemType>& Set<ItemType>::add( const ItemType& item )
{
    if( !contain( item ) )
    {
        rep.add( item );
    }
    return *this;
}

template< class ItemType >
Set<ItemType>& Set<ItemType>::add( const ItemType values[], size_t nbValues )
{
    for( int i = 0; i < nbValues; i++)
    {
        if( isEmpty() )
        {
            rep.add( values[ i ] );
        }
        else if( !contain( values[ i ] ) )
        {
            rep.add( values[ i ] );
        }
    }
    return *this;
}

template< class ItemType >
Set<ItemType>& Set<ItemType>::add( Collection<ItemType>& collection )
{
    ItemType* item = collection.firstItem();
    while( item )
    {
        if( collection.isEmpty() )
        {
            rep.add( *item );
        }
        else if( !contain( *item ) )
        {
            rep.item( *item );
        }
        item = collection.nextItem();
    }
    return *this;
}

template< class ItemType >
Set<ItemType>& Set<ItemType>::add( const Set<ItemType>& set )
{
    ItemType* item = rep.firstItem();
    while( item )
    {
        if( isEmpty() )
        {
            add( *item );
        }
        else if( !contain( *item ) )
        {
            add(* item );
        }
        item = nextItem();
    }
    return *this;
}

template < class ItemType >
void Set<ItemType>::intersect( Set<ItemType>& set, Set<ItemType>& result )
{
    ItemType* item = rep.firstItem();
    while( item )
    {
        if( set.contain( *item ) )
        {
            result.add( *item );
        };
        item = rep.nextItem();
    }
}

template< class ItemType >
Set<ItemType> Set<ItemType>::intersect( Set<ItemType>& rhs )
{
    Set<ItemType> result;
    result.init();
    intersect( result, rhs );
    return result;
}

template< class ItemType >
void Set<ItemType>::setUnion( Set<ItemType>& set, Set<ItemType>& result )
{
    result.reset();
    result.init( *this );
    ItemType* item = set.firstItem();
    while( item )
    {
        if( !contain( *this ) )
        {
            result.add( *item );
        };
        item = set.nextItem();
    }
}

template< class ItemType >
Set<ItemType> Set<ItemType>::setUnion( Set<ItemType>& rhs )
{
    Set<ItemType> result;
    result.init();
    setUnion( rhs, result );
    return result;
}

template< class ItemType >
Set<ItemType> Set<ItemType>::difference( const Set<ItemType>& rhs ) const
{
    //SET DIFFERENCE IN {1, 2, 3} AND {2, 3, 4} IS {1}
    //WHILE, THE DIFFERENCE IN INVERSE SITUATION IS {4}

    Set<ItemType> result; result.init();
    return result;
}

template< class ItemType >
Set<ItemType> Set<ItemType>::symetricDifference( const Set<ItemType>& rhs ) const
{
    // SYMETRIC DIFFERENCE IN {1, 2, 3} AND {2, 3, 4} IS {1, 4

    Set<ItemType> result; result.init();
    return result;
}

template< class ItemType >
Collection<ItemType> Set<ItemType>::asCollection( void ) const
{
    Collection<ItemType> result;
    result.init( rep.items );
    return result;
}

template< class ItemType >
Set<ItemType>& Set<ItemType>::assign( const Set<ItemType>& rhs )
{
    rep.assign( rhs.rep );
    return *this;
}

template< class ItemType >
ItemType* Set<ItemType>::firstItem( void )
{
    return rep.firstItem();
}

template< class ItemType >
ItemType* Set<ItemType>::nextItem( void )
{
    return rep.nextItem();
}

template< class ItemType >
void Set<ItemType>::release( void )
{
    rep.release();
}

template< class ItemType >
void Set<ItemType>::reset( void )
{
    return rep.reset();
}

#endif // SET_H
