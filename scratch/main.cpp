#include <iostream>
#include <cstring>

#ifndef collections_h
#   include "collections.h"
#endif // collections_h

#ifndef word_plain_h
#   include "word_plain.h"
#endif // word_plain_h

#ifndef reader_plain_h
#   include "reader_plain.h"
#endif //reader_plain_h



using namespace std;
/*
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

*/
int main()
{
   Reader reader;
   reader.init(
               "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ", //ALPHABET
               " ,;:-", //DELIMITERS
               "." //ENDOFTEXT
               );
    AssociativeContainer<Word, int> wordFrequencyBinding;
    wordFrequencyBinding.init();

    Word word;
    word.init();
    //OBTIENE LAS PALABRAS DEL TEXTO Y AGREGA LA ASOCIACION <PALABRA, FRECUENCIA>
    //AL CONTENEDOR ASOCIATIVO "WORDFREQUENCYBINDING"

    while( !word.assign( reader.read() ).isNull() ) wordFrequencyBinding.itemAtPos( word )++;
    cout << "words in text: " << read.readed() <<endl;
    //ITERA SOBRE EL CONTENEDOR ASOCIATIVO, MOSTRANDO LOS "BINDINGS"
    //(ASOCIACIONES) <PALABRA, FRECUENCIA> ENCONTRADAS EN EL TEXTO

    cout << "words in list: " << wordFrequencyBinding.count()<<endl;

    Collection<Word> listOfKeys; listOfKeys.init();
    listOfKeys.assign( wordFrequencyBinding.keys() );
    Word* current = listOfKeys.firstItem();
    while( current ) {
        cout << "word: " <<current->c_string()
             << " length: " <<current->asAnsiString().length()
             << "  occurs: " <<wordFrequencyBinding.itemAtPos( *current )
             << " times" <<endl;
        current = listOfKeys.nextItem();
    }

    wordFrequencyBinding.release();

    cout<<endl;

    return 0;
}
