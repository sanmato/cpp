#ifndef TEXT_ANALIZER_H
#define TEXT_ANALIZER_H

#include <stdio.h>

#ifndef set_h
    #include "set.h"
#endif // set_h

template< class basic_type, class lexeme_type>

struct TextAnalizer
{
    enum State {idle, working, ending};
    State status;

    std::istream* input;

    int lexemeCount;

    Set<basic_type> alphabet;
    Set<basic_type> delimiters;
    Set<basic_type> endOfText;

    bool is_end( basic_type item )
    {
        bool result = false;
        if( !endOfText.isEmpty() ) {
            result = endOfText.contain( item );
        } else {
            result = ( bool ) ( !(*input) );
        }
        return result;
    }

    bool initialized;
    bool binded;

    void init( const Set<basic_type>& alphabet,
               const Set<basic_type>& delimiters,
               const Set<basic_type>& endOfText )
    {
        status = idle;
        this->alphabet.init( alphabet );
        this->delimiters.init( delimiters );
        if( !endOfText.isEmpty() ) {
            this->endOfText.init( endOfText );
        } else {
            this->endOfText.init();
        }
        lexemeCount = 0;

        initialized = true;
    }

    void bind( std::istream* stream )
    {
        input = stream;
        binded = true;
    }

    lexeme_type get()
    {
        #ifdef __DEBUG__
            assert( initialized == true );
            assert( binded == true );
        #endif // __DEBUG__

        lexeme_type lexeme;
        lexeme.init();

        bool ready = false;
        while( !ready )
        {
            switch( status )
            {
                case idle:
                    {
                     basic_type item = input->get();
                     if( is_end( item ) ) {
                        ready = true;
                     } else if( alphabet.contain( item ) ) {
                        lexeme.concat( item );
                        lexemeCount++;
                        status = working;
                     }
                    } break;
                case working:
                    {
                        basic_type item = input->get();
                        if( is_end( item ) ) {
                           ready = true;
                           status = ending;
                        } else if( alphabet.contain( item ) ) {
                            lexeme.concat( item );
                        } else if( delimiters.contain( item ) ){
                            ready = true;
                            status = idle;
                        }
                    } break;
                case ending:
                    {
                        ready = true;
                        status = idle;
                    } break;
            }
        }
        return lexeme;
    }

    void release( void )
    {
        alphabet.release();
        delimiters.release();
        endOfText.release();
    }

    void reset( void )
    {
        lexemeCount = 0;
        status = idle;
    }

    int readed( void )
    {
        return lexemeCount;
    }

    int state( void )
    {
        return status;
    }

};


#endif // TEXT_ANALIZER_H
