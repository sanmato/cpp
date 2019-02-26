#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

#include <stdio.h>

#ifndef static_collection_h
#   include "collection.h"
#endif // static_collection_h

/*
UN CONTENEDOR ES UN OBJETO QUE ALMACENA OTROS OBJETOS (SUS ELEMENTOS) , Y QUE TIENE OPERACIONES PARA ACCEDER
A SUS ELEMENTOS. UN CONTENEDOR (EN ESTE CONTEXTO) "POSEE" A SUS ELEMENTOS, ESTO ES EL CICLO DE VIDA DE SUS ELEMENTOS
NO PUEDE EXCEDER AL CICLO DE VIDA DEL CONTENEDOR.

UN CONTENEDOR ASOCIATIVO ES UN TIPO DE CONTENEDOR COMPUESTO POR UNA COLECCION DE CLAVES Y VALORES.
EN UN CONTENEDOR ASOCIATIVO, LA ASOCIACION ENTRE UNA CLAVE Y UN VALOR SE CONOCE COMO "BINDING" Y LA MISMA PALABRA
"BINDING" SUELE UTILIZARSE PARA REFERIRSE AL PROCESO DE CREAR UNA NUEVA ASOCIACION

*/


template <class KeyType, class ValueType>

struct AssociativeContainer {

    Collection<KeyType> itsKeys;
    Collection<ValueType> itsValues;

    void init(void);
    void release(void);
    void reset(void);

    ValueType& add( const KeyType& key, const ValueType& value);

    ValueType& itemAtPos( const KeyType& key);
    ValueType valueforKey( const KeyType& key);
    bool contain( const KeyType& item );
    Collection<KeyType> keys(void);
    size_t count(void);

    KeyType* firstItem(void);
    KeyType* nextItem(void);
};
//Associative Container member functions.

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::init( void )
{
    itsKeys.init();
    itsValues.init();
}

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::release( void )
{
    itsKeys.release();
    itsValues.release();
}

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::reset( void )
{
    itsKeys.reset();
    itsValues.reset();
}

template <class KeyType, class ValueType>
ValueType& AssociativeContainer<KeyType, ValueType>::add( const KeyType& key, const ValueType& value )
{
    long slot = itsKeys.indexOf( key );

    if( slot == -1 ) {
        itsKeys.add( key );
        itsValues.itemAtPos( itsKeys.indexOf( key ) ) = value;
        slot = itsKeys.indexOf( key );
    }
    return itsValues.itemAtPos( slot );
}

template <class KeyType, class ValueType>
ValueType& AssociativeContainer<KeyType, ValueType>::itemAtPos( const KeyType& key )
{
    long slot = itsKeys.indexOf( key );

    if( slot == -1 ) {
        itsKeys.add( key );
        itsValues.itemAtPos( itsKeys.indexOf( key ) ) = ValueType();
        slot = itsKeys.indexOf( key );
    }
    return itsValues.itemAtPos( slot );
}

template <class KeyType, class ValueType>
ValueType AssociativeContainer<KeyType, ValueType>::valueforKey( const KeyType& key)
{
    long slot = itsKeys.indexOf( key )
    return ( slot != -1 ) ? itsValues.itemAtPos( slot ) : ValueType();
}

template <class KeyType, class ValueType>
bool AssociativeContainer<KeyType, ValueType>::contain( const KeyType& item )
{
    return( itsKeys.indexOf( key ) != -1 );
}

template <class KeyType, class ValueType>
Collection<KeyType> AssociativeContainer<KeyType, ValueType>::keys( void )
{
    return itsKeys;
}

template <class KeyType, class ValueType>
size_t AssociativeContainer<KeyType, ValueType>::count( void )
{
    return itsKeys.size();
}

template <class KeyType, class ValueType>
KeyType* AssociativeContainer<KeyType, ValueType>::firstItem( void )
{
    return itsKeys.firstItem();
}

template <class KeyType, class ValueType>
KeyType* AssociativeContainer<KeyType, ValueType>::nextItem( void )
{
    return itsKeys.nextItem();
}
#endif // ASSOCIATIVE_CONTAINER_H
