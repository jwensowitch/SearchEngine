//
//  QueryProcessor.h
//  Project_5
//
//

#ifndef __Project_5__QueryProcessor__
#define __Project_5__QueryProcessor__

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstring>

#include "Indexer.h"
#include "Page.h"
#include "StopWords.h"

using namespace std;

//!  QueryProcessor Class.
/*!
 Boolean Query Processor to handle formatted queries.
 */

class QueryProcessor
{
    
private:
    vector<vector<Page*> > *rawResults;
    vector<Page*> *processedResults;
    Indexer* index;
    StopWords* stopwordlist;
    vector<int> *relevancy;
    unordered_set<string>* stopWords;
    vector<Page*> merge_copy(const vector<Page*>& a,
                             const vector<Page*>& b);
    
public:
    //!  QueryProcessor Constructor.
    /*!
     Takes an Indexer object by pointer to have fast access to Indexer data.
     */
    QueryProcessor(Indexer *);
    //!  QueryProcessor Destructor.
    ~QueryProcessor();
    /*!
     Returns a vector of Page* sorted by relevancy for boolean searches.
     */
    vector<Page*>* process(int structure, string search);
    /*!
     Returns a vector of relevancy integers parallel to the vector of results.
     */
    vector<int>* getRelevancy();
    
};


#endif /* defined(__Project_5__QueryProcessor__) */
