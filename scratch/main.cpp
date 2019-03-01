#include <iostream>
#include <cstring>

#ifndef collections_h
    #include "collections.h"
#endif // collections

#ifndef WORD_PLAIN_H
    #include "word_plain.h"
#endif // WORD_PLAIN_H

#ifndef GENERATIVE_HEADER_H
    #include "generative_header.h"
#endif // GENERATIVE_HEADER_H

#ifndef TEXT_ANALIZER_H
    #include "text_rule.h"
#endif // TEXT_ANALIZER_H



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
    cout << "words in text: " << reader.readed() <<endl;
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
