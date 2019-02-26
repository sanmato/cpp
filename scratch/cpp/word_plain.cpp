#include "word_plain.h"

void Word::init( const char* plainString ) {
    rep.init( plainString );
}

bool Word::isNull( void ) const {
    return rep.isNull();
}

const char* Word::c_string( void ) {
    return rep.c_string();
}

Word& Word::concat( char ch ) {
    rep.concat( ch );
    return *this;
}

Word& Word::assign( const Word& word ) {
    rep.assign( word.rep );
    return *this;
}

Word& Word::assign( const AnsiString& ansiString ) {
    rep.assign( ansiString );
    return *this;
}

AnsiString Word::asAnsiString( void ) const {
    return rep;
}
