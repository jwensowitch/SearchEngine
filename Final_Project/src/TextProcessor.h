//
//  TextProcessor.h
//  Project_5
//
//

#ifndef __Project_5__TextProcessor__
#define __Project_5__TextProcessor__

#include <iostream>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <string>
#include <regex>

#include "Page.h"
#include <boost/tokenizer.hpp>
#include "proter2_stemmer.h"
#include "ReplaceAll.h"

using namespace std;

//! TextProcessor Class.
/*! A class that processes raw text of each page. Includes stop word removal and stemming. Class utilized by Indexer Class */

class TextProcessor
{
    
private:
    queue<string>* queKeyWords;
    unordered_set<string>* uos_stopWords;
    string *s;

public:
    //! TextProcessor Constructor.
    /*! A unordered_set of string stop words must be provided */
    TextProcessor(unordered_set<string>* );
    //! TextProcessor Destructor.
    ~TextProcessor();
    /*! Removes HTML tags from a string*. */
    string* stripHTMLTags(string*);
    /*! Returns a queue of target words to be indexed. */
    queue<string>* process(Page*);
    
};


#endif /* defined(__Project_5__TextProcessor__) */
