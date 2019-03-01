#include "generative_header.h"

#ifndef GENERATIVE_HEADER_H
#define GENERATIVE_HEADER_H

#include <stdio.h>

#ifndef set_h
    #include "set.h"
#endif // set_h


/*int lexemeCount;

bool binded;

void init()
{
    lexemeCount = 0;
}

void release( void )
{

}

void bind( std::istream* stream )
{
    input = stream;
    binded = true;
}

void unbind( std::istream* stream )
{
    binded = false;
}

template< template<typename, typename> class custom_rule>
lexeme_type readWith( custom_rule<basic_type, lexeme_type> rule )
{
    lexeme_type lexeme; lexeme.init();

    lexeme.assign( rule.process( input ) );

    if( !lexeme.isNull() ) lexemeCount++;

    return lexeme;
}

void reset( void )
{
    lexemeCount = 0;
}

int readed( void )
{
    return lexemeCount;
}
*/

template< class lexeme_type >
struct Reader
{
    template<class basic_type>
    struct accepting
    {
        template<std::istream* input>
        struct from
        {
            template<template<typename, typename> class custom_analyzer>
            struct use
            {
                template<template<typename, typename> class custom_rule>
                struct with
                {
                    custom_rule<basic_type, lexeme_type> rule;
                    custom_analyzer<basic_type, lexeme_type> analizer;

                    void init( void )
                    {
                        rule.init();
                        analizer.init();
                        analizer.bind( input );
                    }
                    void release( void )
                    {
                        analizer.release();
                        analizer.unbind( input );
                        rule.release();
                    }

                    void reset( void )
                    {
                        analizer.reset();
                    }

                    lexeme_type read( void )
                    {
                        return analizer.readWith( rule );
                    }

                    int read( void )
                    {
                        return analizer.readWith( rule );
                    }

#endif // text_analizer_h
