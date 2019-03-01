#ifndef READER_PLAIN_H
#define READER_PLAIN_H

#include <stdio.h>

#ifndef set_h
    #include "set.h"
#endif // set_h

#ifndef ansi_string_h
    #include "ansi_string.h"
#endif // ansi_string_h

struct Reader {
    enum States {idle, working, ending};
    States currentState;

    int count;

    Set<char> alphabet;
    Set<char> delimiter;
    Set<char> endOfText;

    void init( const char* alphabet, const char* delimiter, const char* endOfText );

    void release(void);
    void reset(void);

    AnsiString read(void);

    int readed(void);
    int state(void);

};



#endif // READER_PLAIN_H
