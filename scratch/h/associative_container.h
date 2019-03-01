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

    struct Iterator {
        KeyType* currentKey;
        ValueType* currentValue;
        AssociativeContainer<KeyType, ValueType>* associativeContainer;
        Collection<KeyType> keys;

        void init( AssociativeContainer<KeyType, ValueType>* itsAssociativeContainer );
        void release(void);
        void reset(void);

        Iterator& begin(void);
        Iterator& next(void);
        Iterator& end(void);
        bool isNull( void );
        KeyType* key(void);
        ValueType* value(void);

    } iterator;

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

//Associative Container Iterator member functions.

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::Iterator::init( AssociativeContainer<KeyType, ValueType>* itsAssociativeContainer)
{
    associativeContainer = itsAssociativeContainer;
    currentKey = nullptr;
    currentValue = nullptr;
    keys.init( associativeContainer->keys() );
}

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::Iterator::release( void ) {
    keys.release();
}

template <class KeyType, class ValueType>
void AssociativeContainer<KeyType, ValueType>::Iterator::reset( void ) {
    currentKey = nullptr;
    currentValue = nullptr;
    keys.reset();
    keys.init( associativeContainer->keys() );
}

template <class KeyType, class ValueType>
typename AssociativeContainer<KeyType, ValueType>::Iterator& AssociativeContainer<KeyType, ValueType>::Iterator::begin( void ) {
    currentKey = keys.firstItem();
    if( currentKey != nullptr ) currentValue = &( associativeContainer->itemAtPos( *( currentKey ) ) );
    return *this;
}

template <class KeyType, class ValueType>
typename AssociativeContainer<KeyType, ValueType>::Iterator& AssociativeContainer<KeyType, ValueType>::Iterator::next( void ) {
    currentKey = keys.nextItem();
    if( currentKey != nullptr ) currentValue = &( associativeContainer->itemAtPos( *( currentKey ) ) );
    return *this;
}

template <class KeyType, class ValueType>
typename AssociativeContainer<KeyType, ValueType>::Iterator& AssociativeContainer<KeyType, ValueType>::Iterator::end( void ) {
    currentKey = nullptr;
    currentValue = nullptr;
    return *this;
}

template <class KeyType, class ValueType>
bool AssociativeContainer<KeyType, ValueType>::Iterator::isNull( void ) {
    return currentKey == nullptr;
}

template <class KeyType, class ValueType>
KeyType* AssociativeContainer<KeyType, ValueType>::Iterator::key( void ) {
    return currentKey;
}

template <class KeyType, class ValueType>
ValueType* AssociativeContainer<KeyType, ValueType>::Iterator::value( void ) {
    return ( currentKey ) ? ( &( associativeContainer->itemAtPos( *( currentKey ) ) ) ) : ( ValueType* )
        nullptr;
}

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
    long slot = itsKeys.indexOf( key );
    return ( slot != -1 ) ? itsValues.itemAtPos( slot ) : ValueType();
}

template <class KeyType, class ValueType>
bool AssociativeContainer<KeyType, ValueType>::contain( const KeyType& key )
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
