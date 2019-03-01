#ifndef ANSI_STRING_H
#define ANSI_STRING_H

#include <stdio.h>

#ifndef COLLECTION_H
    #include "collection.h"
#endif // COLLECTION_H

struct AnsiString
{
    enum { NULL_CHAR = '\0', ANSI_STRING_DEFAULT_LENGTH = 255, CONTAINER_CAPACITY = ANSI_STRING_DEFAULT_LENGTH + 1};

    char items[ CONTAINER_CAPACITY ];

    size_t first;
    char* current;
    size_t last;
    unsigned long count;

    bool initialized;

    //PRIVATE HELPERS FUNCTIONS

    char* allocate( size_t requiredCapacity = CONTAINER_CAPACITY );
    void collectionAsString( Collection<char> collection, char* string );
    static void simple_layout( const char& item );
    void KMPBuildPartialMatchTable( const char* pattern, int partialMatch[] ) const;

    //INITIALIZERS FAMILY FUNCTIONS

    void init( void );
    void init( char ch );
    void init( const char* plainString );
    void init( const Collection<char>& collection );
    void init( const AnsiString& string );

    //RELEASE & RESET FAMILY FUNCTIONS

    void release( void );
    void reset( void );

    //CONCAT FAMILY FUNCTIONS

    AnsiString& concat( const char& item );
    AnsiString& concat( const char* plainString );
    AnsiString& concat( Collection<char>& collection );
    AnsiString& concat( const AnsiString& string );

    //INSERT FAMILY FUNCTIONS

    AnsiString& insert( const char& item );
    AnsiString& insertAtPos( unsigned long pos, const char& item );

    AnsiString& insert( const char* plainString );
    AnsiString& insertAtPos( unsigned long pos, const char* plainString );

    AnsiString& insert( const AnsiString& string );
    AnsiString& insertAtPos( unsigned long pos, const AnsiString& string );

    //REMOVE FAMILY FUNCTIONS

    AnsiString& remove( unsigned long pos, unsigned long count );
    AnsiString& remove( const char& item );
    AnsiString& remove( const char* plainString );
    AnsiString& remove( const AnsiString& string );
    AnsiString& removeAll( const char& item );
    AnsiString& removeAll( const char* plainString );
    AnsiString& removeAll( const AnsiString& string );

    //SUBSTRING FUNCTION

    AnsiString subString( unsigned long start, unsigned long count ) const;

    //TYPE CONVERSION

    const char* c_string( void ) const;
    Collection<char> asCollection( void ) const;

    //ASSIGN A.K.A "="

    AnsiString& assign( const char& rhs );
    AnsiString& assign( const char* rhs );
    AnsiString& assign( const Collection<char>& rhs );
    AnsiString& assign( const AnsiString& rhs );

    //RELATIONAL OPERATORS FUNCTIONS

    bool equal( const char* rhs ) const;
    bool less( const char* rhs ) const;
    bool lessOrEqual( const char* rhs ) const;
    bool greather( const char* rhs ) const;
    bool greatherOrEqual( const char* rhs ) const;

    //QUERIES

    long pos( const char& item ) const;
    long pos( const char* plainString ) const;
    long pos( const Collection<char>& collection ) const;
    long pos( AnsiString& string ) const;
    Collection<int> ocurrencesOf( const AnsiString& pattern ) const;
    size_t length( void ) const;
    size_t size( void ) const;
    size_t capacity( void ) const;
    bool isNull( void ) const;
    char& itemAtPos( int pos );
    char itemAtPos( int pos ) const;

    //UTILITIES FAMILY

    static AnsiString fillChar( const char& ch, size_t nbChars = ANSI_STRING_DEFAULT_LENGTH );
    AnsiString upCase( void ) const;
    AnsiString lowCase( void ) const;
    AnsiString reverse( void ) const;

    void dump( void( *layout )( const char& ch ) = simple_layout ) const;

};


#endif // ANSI_STRING_H
