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
#include <array>
#include <algorithm>
#include <cmath>

class SortingCompetition
{
    
private:
    std :: string inputFile;
    std :: ifstream input;
    std :: vector<short*> words;
    std :: vector<short*> specialWords;
    size_t wordsSize;
    size_t specWordsSize;
    short* tempShorts;
    unsigned int* array1_4;
    unsigned int* array5;
    unsigned int* count5;
    unsigned int** sumArr;
    unsigned int* lenArr;
    unsigned int* numInts;
    size_t* indexes;
    size_t* indexArr;
    int recurs;
    size_t firstEle;
    size_t lastEle;
    size_t swapIndex;
    
    
    
public:
    SortingCompetition(const std :: string& inputFileName);
    ~SortingCompetition();
    void setFileName(const std :: string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void insertionSort(unsigned int, unsigned int);
    void gapSort(size_t, size_t);
    void quickSortA(size_t, size_t);
    void quickSort(size_t, size_t);
    void medianOfThree(size_t, size_t);
    int intcmp(unsigned int*, unsigned int*, size_t, size_t);
    int intcmp(unsigned int, unsigned int);
    void outputData(const std :: string& outputFileName);
    size_t getWordsSize();
    void printData();
    
};

#endif /* defined(__Wensowitch_Project3__SortingCompetition__) */
