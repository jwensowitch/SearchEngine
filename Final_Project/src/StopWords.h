//
//  StopWords.h
//  Project_5
//
//

#ifndef __Project_5__StopWords__
#define __Project_5__StopWords__

#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>

using namespace std;

//!  StopWords Class.
/*!
 A class to handle stop words.
 */

class StopWords
{
    
private:
    unordered_set<string>* stop_words;
    ifstream file;
    string filename;
    string word;
    
public:
    //!  StopWords Constructor.
    /*!
     Built from a filename.
     */
    StopWords(string);
    //!  StopWords Destructor.

    ~StopWords();
    /*!
     Returns stopwords in a unordered_set for fast comparison.
     */
    unordered_set<string>* get_list();
    
};


#endif /* defined(__Project_5__StopWords__) */
