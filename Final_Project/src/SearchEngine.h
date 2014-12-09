//
//  SearchEngine.h
//  Project_5
//
//  Created by Admin on 11/16/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#ifndef __Project_5__SearchEngine__
#define __Project_5__SearchEngine__

#include <iostream>
#include <iomanip>

#include "XMLParser.h"
#include "Page.h"
#include "TextProcessor.h"
#include "Indexer.h"
#include "QueryProcessor.h"

//!  SearchEngine Class
/*!
A driver for the search engine.
 */

class SearchEngine
{
    
private:
    XMLParser *pXml;
    queue<Page*> *rawPageQueue;
    Indexer *index;
    int structure;
    vector<Page*> *results;
    QueryProcessor *searchProcessor;
    bool is_number(const std::string& s);
    void clearLoad();
    void iterativeSearch();
    void search(int);
    void parse();
    void loadIndex();
    void addDocs();
    void timeIndex();

public:
    //!  SearchEngine Constructor.
    /*!
     Takes an intial .xml file to build index.
     */
    SearchEngine(string InputXMLfile);
    //!  SearchEngine Destructor.
    ~SearchEngine();
    /*!
     Intialize and Start Search Engine Instance
     */
    int start();
    
};

#endif /* defined(__Project_5__SearchEngine__) */
