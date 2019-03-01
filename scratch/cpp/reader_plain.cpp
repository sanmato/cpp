#include "reader_plain.h"
#include <iostream>

void Reader::init(const char* alphabet, const char* delimiter, const char* endOfText) {
    currentState = idle;
    count = 0;

    this->alphabet.init(alphabet, strlen(alphabet));
    this->delimiter.init(delimiter, strlen(delimiter));
    this->endOfText.init(endOfTenxt, strlen(endOfText));
}

void Reader::release(void) {
    alphabet.release();
    delimiter.release();
    endOfText.release();
}

void Reader::reset(void) {
    count = 0;
    currentState = idle;
}

AnsiString Reader::read(void) {
    AnsiString string; string.init();

    bool done = false;
    while(!done) {
        if( currentState == idle ) {
            char ch = std::cin.get();
            if( endOfText.contain(ch) ) {
                currentState = ending;
            } else if( alphabet.contain(ch) ) {
                string.concat(ch);
                currentState = working;
                count++;
            } else if( delimiter.contain(ch) ) {
                ;
            }
        } else if( currentState == working ) {
            char ch = std::cin.get();
            if( endOfText.contain( ch ) ) {
                done = true;
                currentState = ending;
            } else if( alphabet.contain( ch ) ) {
                string.concat(ch);
                currentState = working;
            } else if( delimiter.contain( ch ) ) {
                done = true;
                currentState = idle;
            }
        } else if( currentState == ending ) {
            done = true;
            currentState = idle;
        }
    }
    return string;
}

int Reader::readed(void) {
    return count;
}

int Reader::state(void) {
    return currentState;
}
