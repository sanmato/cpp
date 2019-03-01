#ifndef TEXT_RULE_H
#define TEXT_RULE_H

#include <stdio.h>
#include <iostream>

#ifndef set_h
    #include "set.h"
#endif // set_h

template<class basic_type, class lexeme_type>
struct TextRule
{
    enum State{idle, working};
    State status;

    bool initialized;

    Set<basic_type> alphabet;
    Set<basic_type> delimiter;
    Set<basic_type> endOfText;

    void init( void )
    {
        status = idle;

        alphabet.init( "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ", 56 );
        delimiter.init( " ,;:-", 5 );
        endOfText.init( ".", 1 );
        initialized = true;
    }

    lexeme_type process( std::istream* stream )
    {
        #ifdef __DEBUG__
            assert( initialize == true );
        #endif // __DEBUG__

        lexeme_type lexeme;
        lexeme.init();

        bool ready = false;
        switch( status )
        {
            case idle:
            {
                basic_type item = stream->get();
                if( endOfText.contain( item ) || ( ( bool )!(*stream) ) ){
                    ready = true;
                } else if( alphabet.contain( item ) ) {
                    lexeme.concat( item );
                    status = working;
                }
            } break;

            case working:
            {
                basic_type item = stream->get();
                if( endOfText.contain( item ) || ( ( bool )!(*stream) ) ){
                    ready = true;
                    stream->putback( item );
                } else if( alphabet.contain( item ) ) {
                    lexeme.concat( item );
                } else if( delimiter.contain( item ) ) {
                    ready = true;
                    status = idle;
                }
            } break;
        }
    return lexeme;
    }

    void release( void )
    {
        alphabet.release();
        delimiter.release();
        endOfText.release();
    }

    void reset( void )
    {
        status = idle;
    }

    int state( void )
    {
        return status;
    }
};



#endif // TEXT_RULE_H
