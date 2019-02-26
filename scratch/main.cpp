#include <iostream>
#include <cstring>

#ifndef collection_h
#   include "collection.h"
#endif // collection_h

#ifndef set_h
#   include "set.h"
#endif // set_h

#ifndef associative_container_h
#   include "associative_container.h"
#endif //associative_container



using namespace std;

struct Word {
    enum{MAX_STRING_LENGTH = 254, CONTAINER_CAPACITY = MAX_STRING_LENGTH +1 };
    char items [CONTAINER_CAPACITY];

    bool isNull(void) {
        return items[0] == '\0';
    }

    void init(const char* plainString = "") {
        strcpy(items, plainString);
    }

    const char* c_string (void) {
        return &(items[0]);
    }

    Word& concat( char ch ) {
        size_t len = strlen(items);
        items[len] = ch;
        items[len +1 ] = '\0';
        return *this;
    }

    Word& assign( const Word& word ) {
        strcpy(items, word.items);
        return *this;
    }

};

typedef const char* SetOfChar;

SetOfChar alphabet = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
SetOfChar delimiter = " ,;:";
SetOfChar endOfText = ".";

bool contain(SetOfChar set, char ch) {
    size_t cardinal = strlen(set);
    size_t idx = 0;
    for ( ; idx < cardinal && set[idx] != ch; idx++);
    return (idx < cardinal);
}

Word getWordFromText(void) {
    enum States {idle, working, ending};
    static States state = idle;
    Word word;
    word.init();
    bool done = false;
    while ( !done ) {
        if(state == idle ) {
            char ch = cin.get();
            if(contain(endOfText, ch ) ) {
                //done = true;
                //state = idle;
                state = ending;
            }else if (contain(alphabet, ch ) ) {
                word.concat(ch);
                state = working;
            }else if (contain(delimiter, ch ) ) {
                ;
            }
        } else if(state == working) {
            char ch = cin.get();
            if( contain(endOfText, ch ) ) {
                done = true;
                //state = idle;
                state = ending;
            }else if( contain(alphabet, ch ) ) {
                word.concat(ch);
            }else if( contain(delimiter, ch ) ) {
                done = true;
                state = idle;
            }
        } else if(state == ending) {
            done = true;
            state = idle;
        }
    }
    return word;
}

void process(Word thisWord) {
    cout<<thisWord.c_string()<<endl;
}
int main()
{
   /* unsigned count = 0;
    Word word;
    word.init();
    word.assign(getWordFromText());
    while(!word.isNull()) {
        process(word);
        count++;
        word.assign(getWordFromText());
    }
    cout<<"words in text: "<<count<<endl; */

    AssociativeContainer<Word, int> wordFrequencyBinding;
    wordFrequencyBinding.init();

    Word word;
    word.init();
    size_t wordsInText = 0;

    while(!word.assign(getWordFromText() ).isNull() ) {
        wordFrequencyBinding.itemAtPos( word )++;
        wordsInText++;
    }

    cout<< "words in text: " <<wordsInText<<endl;

    cout<< "words in list: " <<wordFrequencyBinding.count()<<endl;
    Collection<Word> listOfKeys; listOfKeys.init();
    listOfKeys.assign(wordFrequencyBinding.keys() )
    Word* current = listOfKeys.firstItem();
    while(current) {
        cout<< "word: " <<current->c_string()
            << "  occurs: " <<wordFrequencyBinding.itemAtPos( *current )
            << " times" <<endl;
        current = listOfKeys.nextItem();
    }

    wordFrequencyBinding.release();

    cout<<endl;

    return 0;
}
