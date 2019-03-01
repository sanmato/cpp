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

int main()
{
    Reader<Word>::accepting<char>::from< &cin >::use<Analizer>::with<TextRule> reader;
    reader.init();

    typedef int Frequency;
    AssociativeContainer<Word, Frequency> wordFrequencyBinding;
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

    AssociativeContainer<Word, Frequency>::Iterator iterator;
    iterator.init( &wordFrequencyBinding );
    for( iterator.begin(); !iterator.isNull(); iterator.next() ) {
        cout << "word: " <<iterator.key()->c_string() << "\t"
             << "length: " <<iterator.key()->asAnsiString().length() << "\t"
             << "occurs: " <<*( iterator.value() ) << "\t"
             << "times" <<endl;
    }

    word.release();
    iterator.release();
    wordFrequencyBinding.release();
    reader.release();

    cout<<endl;

    return 0;
}
