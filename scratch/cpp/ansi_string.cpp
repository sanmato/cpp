#include "ansi_string.h"

#include <iostream>
#include <cstring>

// PRIVATE HELPERS FUNCTIONS

char* AnsiString::allocate( size_t requiredCapacity )
{
    memset( items, NULL_CHAR, requiredCapacity );
    return items;
}

void AnsiString::collectionAsString( Collection<char> collection, char* rep )
{
    int idx = 0;
    char* item = collection.firstItem();
    while( item )
    {
        rep[ idx++ ] = *item;
        item = collection.nextItem();
    }
    rep[ idx ] = NULL_CHAR;

    first = 0;
    current = 0;
    last = first + collection.size() - 1;

    count = collection.size();
}

void AnsiString::simple_layout( const char& item )
{
    std::cout << item;
}

//INITIALIZERS FAMILY FUNCTIONS

void AnsiString::init( void )
{
    allocate();

    first = 0;
    current = 0;
    last = 0;

    count = 0;

    initialized = true;
}

void AnsiString::init( char ch )
{
    allocate();

    items[ 0 ] = ch;
    first = 0;
    current = 0;
    last = 1;

    count = 1;

    initialized = true;
}

void AnsiString::init( const char* string )
{
    allocate();

    size_t stringLength = strlen( string );
    memcpy( items, string, stringLength * sizeof( char ) );

    first = 0;
    current = 0;
    last = stringLength - 1;

    count = stringLength;

    initialized = true;
}

void AnsiString::init( const Collection<char>& collection )
{
    #ifdef __DEBUG__
        assert( collection.initialized );
        assert( !( collection.capacity() > CONTAINER_CAPACITY ) )
    #endif // __DEBUG__

    allocate();

    collectionAsString( collection, items );

    first = 0;
    current = 0;
    last = collection.size() - 1;
    count = collection.size();

    initialized = true;
}

void AnsiString::init( const AnsiString& string )
{
    #ifdef __DEBUG__
        assert( string.initialized )
    #endif // __DEBUG__

    size_t stringSize = string.count + 1;
    allocate();

    memcpy( items, string.items, stringSize * sizeof( char ) );

    first = 0;
    current = 0;
    last = string.count - 1;

    count = string.count;

    initialized = true;
}

//RELEASE & RESET FAMILY FUNCTIONS

void AnsiString::release( void )
{
    reset();
}

void AnsiString::reset( void )
{
    #ifdef __DEBUG__
        assert( items.initialized );
    #endif // __DEBUG__

    init();
}

//ADD FAMILY FUNCTIONS

AnsiString& AnsiString::concat( const char& ch )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( [ ( count + 1 > CONTAINER_CAPACITY ) ] )
    #endif // __DEBUG__

    //MIRAR ESTO

    Collection<char> collection;
    collection.init( items, count );

    collection.add( ch );

    collectionAsString( collection, items );

    collection.release();

    return *this;
}

AnsiString& AnsiString::concat( const char* plainString )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert(  ( ( count + strlen( plainString ) > CONTAINER_CAPACITY ) )  )
    #endif // __DEBUG__

    Collection<char> result;
    result.init( items, count );

    result.add( plainString, strlen( plainString ) );

    collectionAsString( result, items );

    result.release();

    return *this;
}

AnsiString& AnsiString::concat( Collection<char>& collection )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( [ ( count + strlen( plainString ) > CONTAINER_CAPACITY ) ] )
    #endif // __DEBUG__

    Collection<char> result;
    result.init( items, count );
    result.add( collection );

    collectionAsString( result, items );

    result.release();

    return *this;
}

AnsiString& AnsiString::concat( const AnsiString& string )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( [ ( count + strlen( plainString ) > CONTAINER_CAPACITY ) ] )
    #endif // __DEBUG__

    Collection<char> result;
    result.init( items, count );
    result.add( string.items, string.count );

    collectionAsString( result, items );

    result.release();

    return *this;
}

//INSERT FAMILY

AnsiString& AnsiString::insert( const char& item )
{
    return insertAtPos( 0, item );
}


AnsiString& AnsiString::insertAtPos( unsigned long pos, const char& item )
{
    char dummyString[ 2 ] = { NULL_CHAR, NULL_CHAR };
    dummyString[ 0 ] = item;
    return insertAtPos( pos, dummyString ); //;
}

AnsiString& AnsiString::insert( const char* plainString )
{
    return insertAtPos( 0, plainString );
}

AnsiString& AnsiString::insertAtPos( unsigned long pos, const char* plainString )
{
    #ifdef __DEBUG
        assert( initialized );
        assert( plainString != nullptr );
        assert( [ ( count + strlen( plainString ) > CONTAINER_CAPACITY ) ] )
    #endif // __DEBUG

    char result[ CONTAINER_CAPACITY ];
    memset( result, NULL_CHAR, CONTAINER_CAPACITY * sizeof( char ) );

    if( pos<= 0 )
    {
        strcpy( result, plainString );
        strcat( result, items );
    }
    else if( ( pos > 0 ) && ( pos < count ) )
    {
        strcpy( result, (*this).subString( 0, pos ).c_string() );
        strcat( result, plainString );
        strcat( result, (*this).subString( pos, count ).c_string() );
    }
    else if( pos >= count )
    {
        strcpy( result, items );
        strcat( result, plainString );
    }
    release();
    init( result );

    return *this;
}

AnsiString& AnsiString::insert( const AnsiString& string )
{
    return insertAtPos( 0, string.c_string() );
}

AnsiString& AnsiString::insertAtPos( unsigned long pos, const AnsiString& string )
{
    return insertAtPos( pos, string.c_string() );
}

//REMOVE FAMILY

AnsiString& AnsiString::remove( unsigned long pos, unsigned long nbChars )
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    if( nbChars <= 0 ) return *this;

    if( pos <= 0 )
    {
        assign( subString( nbChars, count ) );
    }
    else if( ( pos < 0 ) && ( pos < count ) )
    {
        //assign( subString( 0, pos - 1 ).concat( subString( pos + nbChars, count ) ) );
        assign( subString( 0, pos ).concat( subString( pos + nbChars, count ) ) );
    }
    else if( pos >= count )
    {
        assign( subString( 0, pos - 1 ) );
    }

    return *this;

    return *this;
}

AnsiString& AnsiString::remove( const char& item )
{
    char dummyString[ 2 ] = { NULL_CHAR, NULL_CHAR };
    dummyString[ 0 ] = item;

    long posOfDummyString = pos( dummyString );
    if( posOfDummyString == -1 ) return *this;

    return remove( posOfDummyString, 1 );
}

AnsiString& AnsiString::remove( const char* plainString )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( plainString != nullptr );
    #endif // __DEBUG__

    long posOfPlainString = pos( plainString );
    if( posOfPlainString == -1 ) return *this;

    return remove( posOfPlainString, strlen( plainString ) );
}

AnsiString& AnsiString::remove( const AnsiString& string )
{
    long posOfString = pos( string.items );
    if( posOfString == -1 ) return *this;

    return remove( posOfString, string.count );
}

AnsiString& AnsiString::removeAll( const char& item )
{
    char dummyString[ 2 ] = { NULL_CHAR, NULL_CHAR };
    dummyString[ 0 ] = item;

    return removeAll( dummyString );
}

AnsiString& AnsiString::removeAll( const char* plainString )
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( plainString != nullptr );
    #endif // __DEBUG__

    AnsiString pattern;
    pattern.init( plainString );
    Collection<int> matches;
    matches.init( ocurrencesOf( pattern ) );

    int* current = matches.firstItem();
    int offset = 0;
    while( current )
    {
        remove( *current - offset, pattern.count );
        offset += pattern.count;
        current = matches.nextItem();
    }

    pattern.release();
    matches.release();

    return *this;
}

AnsiString& AnsiString::removeAll( const AnsiString& string )
{
    return removeAll( string.c_string() );
}

//SUBSTRING FUNCTION

AnsiString AnsiString::subString( unsigned long start, unsigned long count ) const
{
    AnsiString result;
    Collection<char> collection;
    collection.init( ( *this ).asCollection() );
    collection.assign( collection.outerSlice( start, start + count - 1 ) );
    result.init( collection );
    return result;
}

//TYPE CONVERSION

const char* AnsiString::c_string( void ) const
{
    #ifdef __DEBUG__
        assert( items 1= ( char* ) NULL_PTR );
    #endif // __DEBUG__

    return items;
}

Collection<char> AnsiString::asCollection( void ) const
{
    Collection<char> collection;
    collection.init( items, count );
    return collection;
}

//ASSIGN A.K.A OPERATOR =

AnsiString& AnsiString::assign( const char& rhs )
{
    release();
    init( rhs );
    return *this;
}

AnsiString& AnsiString::assign( const char* rhs )
{
    release();
    init( rhs );
    return *this;
}

AnsiString& AnsiString::assign( const Collection<char>& rhs )
{
    release();
    init( rhs );
    return *this;
}

AnsiString& AnsiString::assign( const AnsiString& rhs )
{
    release();
    init( rhs );
    return *this;
}

//RELATIONAL OPERATORS FAMILY

bool AnsiString::equal( const char* rhs ) const
{
    return strcmp( items, rhs ) == 0 ? true : false;
}

bool AnsiString::less( const char* rhs ) const
{
    return strcmp( items, rhs ) < 0 ? true : false;
}

bool AnsiString::lessOrEqual( const char* rhs ) const
{
    return !greather( rhs );
}

bool AnsiString::greather( const char* rhs ) const
{
    return strcmp( items, rhs ) > 0 ? true : false;
}

bool AnsiString::greatherOrEqual( const char * rhs ) const
{
    return !less( rhs );
}

//QUERIES

long AnsiString::pos( const char& item ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    long not_found = -1;
    size_t index = 0;
    for( ; ( index < count ) && ( items[ index ] != item ); index++ )
    {
         ;
    }

    return( index < count ) ? index : not_found;
}

long AnsiString::pos( const char* plainString ) const
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( plainString != nullptr );
    #endif // __DEBUG__

    //KNUTH-MORRIS-PRATT ALGORITHM

    size_t patternLength = strlen( plainString );
    if( patternLength == 0 ) return -1;

    size_t stringLength = count;
    int partialMatch[ patternLength ];

    KMPBuildPartialMatchTable( plainString, partialMatch );

    int currentStringCharacter = 0;
    int currentPatternCharacter = 0;
    while( currentStringCharacter < stringLength )
    {
        if( currentPatternCharacter == -1 )
        {
            currentStringCharacter++;
            currentPatternCharacter = 0;
        }
        else if( items[ currentStringCharacter ] == plainString[ currentPatternCharacter ] )
        {
            currentStringCharacter++;
            currentPatternCharacter++;
            if( currentPatternCharacter == patternLength ) return currentStringCharacter - currentPatternCharacter;
        }
        else
        {
            currentPatternCharacter = partialMatch[ currentPatternCharacter ];
        }
    }
    return -1;
}

long AnsiString::pos( const Collection<char>& collection ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    AnsiString string;
    string.init( collection );

    return pos( string.items );
}

long AnsiString::pos( AnsiString& string ) const
{
    #ifdef __DEBUG__
        assert( initialized );
    #endif // __DEBUG__

    return pos( string.items );
}

void AnsiString::KMPBuildPartialMatchTable( const char* pattern, int partialMatch[] ) const
{
    //KNUTH-MORRIS-PRATT ALOGORITHM, PARTIAL MATCH TABLE

    size_t patternLength = strlen( pattern );
    int currentPatternCharacter;
    partialMatch[ 0 ] = -1;
    for( int i = 1; i < patternLength; i++ )
    {
        currentPatternCharacter = partialMatch[ i - 1 ];
        while( currentPatternCharacter >= 0 )
        {
            if( pattern[ currentPatternCharacter ] == pattern[ i - 1 ] ) break;
            else currentPatternCharacter = partialMatch[ currentPatternCharacter ];
        }
        partialMatch[ i ] = currentPatternCharacter + 1;
    }
}

Collection<int> AnsiString::ocurrencesOf( const AnsiString& pattern ) const
{
    #ifdef __DEBUG__
        assert( initialized );
        assert( pattern.initialized );
    #endif // __DEBUG__

    //KNUTH-MORRIS-PRATT ALGORITHM

    size_t stringLength = length();
    size_t patternLength = pattern.length();

    Collection<int> ocurrences;
    ocurrences.init();

    if( patternLength != 0 || stringLength != 0 )
    {
        int partialMatch[ patternLength ];
        KMPBuildPartialMatchTable( pattern.c_string(), partialMatch );

        //SEARCH PHASE

        int currentStringCharacter = 0;
        int currentPatternCharacter = 0;
        int matches = 0;
        while( currentStringCharacter < stringLength )
        {
            if( currentPatternCharacter == -1 )
            {
                currentStringCharacter++;
                currentPatternCharacter = 0;
            }
            else if( items[ currentStringCharacter ] == pattern.itemAtPos( currentPatternCharacter ) )
            {
                currentStringCharacter++;
                currentPatternCharacter++;
                if( currentPatternCharacter == patternLength )
                {
                    //OCURRENCES FOUND
                    ocurrences.add( currentStringCharacter - currentPatternCharacter );
                    currentPatternCharacter = 0;
                }
                matches++;
            }
            else
            {
                currentPatternCharacter = partialMatch[ currentPatternCharacter ];
            }
        }
    }
    return ocurrences;
}

size_t AnsiString::length( void ) const
{
    return count;
}

size_t AnsiString::size( void ) const
{
    return count + 1;
}

size_t AnsiString::capacity( void ) const
{
    return CONTAINER_CAPACITY;
}

bool AnsiString::isNull( void ) const
{
    #ifdef __DEBUG__
        assert( items != ( char* ) NULL_PTR );
    #endif // __DEBUG__

    return ( items[ 0 ] == NULL_CHAR );
}

char& AnsiString::itemAtPos( int pos )
{
    #ifdef __DEBUG__
        assert( ( pos >= 0 ) && ( pos < count ) );
    #endif // __DEBUG__

    return items[ pos ];
}

char AnsiString::itemAtPos( int pos ) const
{
    #ifdef __DEBUG__
        assert( ( pos >= 0 ) && ( pos < count ) );
    #endif // __DEBUG__

    return items[ pos ];
}

//UTILITIES FAMILY

AnsiString AnsiString::fillChar( const char& ch, size_t nbChars )
{
    AnsiString filledString;
    filledString.init();
    for( size_t pos = 0; pos < nbChars; pos++ ) filledString.items[ pos ] = ch;
    return filledString;
}

AnsiString AnsiString::upCase( void ) const
{
    AnsiString upCaseString;
    upCaseString.init( *this );
    for( size_t pos = 0; pos < count; pos++ )
    {
        if( upCaseString.items[ pos ] >= 'a' && upCaseString.items[ pos ] <= 'z' )
        {
            upCaseString.items[ pos ] = upCaseString.items[ pos ] - ( 'a' - 'A' );
        }
    }
    return upCaseString;
}

AnsiString AnsiString::lowCase( void ) const
{
    AnsiString lowCaseString;
    lowCaseString.init( *this );
    for( size_t pos = 0; pos < count; pos++ )
    {
        if( lowCaseString.items[ pos ] >= 'A' && lowCaseString.items[ pos ] <= 'Z')
        {
            lowCaseString.items[ pos ] = lowCaseString.items[ pos ] + ( 'a' - 'A' );
        }
    }
    return lowCaseString;
}

AnsiString AnsiString::reverse( void ) const
{
    AnsiString reverseString;
    reverseString.init( *this );
    for( unsigned long first = 0, last = count - 1; first < last; first++, last-- )
    {
        reverseString.itemAtPos( (int)first ) = items[ last ];
        reverseString.itemAtPos( (int)last ) = items[ first ];
    }
    return reverseString;
}

void AnsiString::dump( void (*layout)(const char& ch ) ) const
{
    Collection<char> dummy;
    dummy.init( items, count );
    dummy.dump( layout );
    dummy.release();
}
