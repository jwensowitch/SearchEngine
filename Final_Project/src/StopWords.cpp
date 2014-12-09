//
//  StopWords.cpp
//  Project_5
//
//

#include "StopWords.h"

StopWords::StopWords(string _filename) : filename(_filename)
{
    stop_words = new unordered_set<string>;
    file.open(filename);
    while (getline(file, word))
    {
        stop_words->insert(word);
    }
}

unordered_set<string>* StopWords::get_list()
{
    return stop_words;
}

StopWords::~StopWords()
{
    
}