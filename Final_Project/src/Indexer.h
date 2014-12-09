//
//  Indexer.h
//  Project_5
//
//  Created by Admin on 11/15/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#ifndef __Project_5__Indexer__
#define __Project_5__Indexer__

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "avl_tree.h"
#include "XMLParser.h"
#include "TextProcessor.h"
#include "StopWords.h"
#include <sparsehash/dense_hash_map>

//!  Indexer Class.
/*!
 A class that handles building the AVL or Hash Map index.
 */

class Indexer
{
    
private:
    TextProcessor* textParser;
    google::dense_hash_map<string, vector<Page*>*, hash<string>>* mapind;
    ag::avltree::AvlTree<string, vector<Page*>*>* avlind;
    StopWords* stopwordlist;
    unordered_set<string>* duplicateCheck;
    unordered_set<string>::const_iterator probe;
    vector<Page*> emptyVector;
    string* word;
  
public:
    //!  Indexer Constructor.
    Indexer();
    //!  Indexer Destructor.
    ~Indexer();
    /*!
     Adds a Page by pointer to the Avl Index
     */
    void indexAvl(Page*);
    /*!
     Adds a Page by pointer to the Hash Map Index
     */
    void indexMap(Page*);
    /*!
     Returns a vector of pages for a single string search. 
     int var = 0: Hash Map 
     int var = 1: Avl Tree
     */
    vector<Page*> getListOfPages(int, string);
    /*!
     Clears both indexes leaving them NULL
     */
    void clearIndices();
    
};



#endif /* defined(__Project_5__Indexer__) */
