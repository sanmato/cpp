#ifndef WORD_PLAIN_H
#define WORD_PLAIN_H

#include <stdio.h>

#ifndef ansi_string_h
#   include "ansi_string.h"
#endif // ansi_string_h

struct Word {
    AnsiString rep;

    void init( const char* plainString="");
    void release( void );

    bool isNull( void ) const;
    const char* c_string( void );

    Word& concat( char ch );
    Word& assign( const Word& word );
    Word& assign( const AnsiString& ansiString );

    AnsiString asAnsiString( void ) const;

};


#endif // WORD_PLAIN_H
