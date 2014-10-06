//
//  SortingCompetition.h
//  Wensowitch_Project3
//

#ifndef __Wensowitch_Project3__SortingCompetition__
#define __Wensowitch_Project3__SortingCompetition__

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class SortingCompetition {

private:
    string inputFile;
    ifstream input;
    vector<string> words;
    size_t wordsSize;
    string* wordsCopy;
    
public:
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const string& outputFileName);
    
};

#endif /* defined(__Wensowitch_Project3__SortingCompetition__) */
