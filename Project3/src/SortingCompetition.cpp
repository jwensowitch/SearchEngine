//
//  SortingCompetition.cpp
//  Wensowitch_Project3
//
//  Created by Admin on 10/1/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#include "SortingCompetition.h"


SortingCompetition::SortingCompetition(const string& inputFileName) : input(inputFileName)
{
}


void SortingCompetition::setFileName(const string& inputFileName)
{
}


bool SortingCompetition::readData()
{
    string tempWords;
    if(!input.is_open())
    {
        cerr << "File Could Not Be Opened" << endl;
        return 0;
    }
    else
    {
        int index = 0;
        words.clear();
        
        while (!input.eof())
        {
            input >> tempWords;
            words.push_back(tempWords);
            index++;
        }
        
        wordsSize = words.size();
        
        input.close();
        
        return 1;
    }
}


bool SortingCompetition::prepareData()
{

    wordsCopy = new string[wordsSize];      //*DYNAMIC
    
    copy(words.begin(), words.end(), wordsCopy);

    return 0;
}

void SortingCompetition::sortData()
{
    size_t i = 0, j = 0, gap, tempLength;
    string tempWord;
    for(gap = wordsSize/2; gap > 0; gap/= 2)
    {
        for(i = gap; i < wordsSize; ++i)
        {
            tempLength = wordsCopy[i].length();
            for(j = i; j >= gap; j-= gap)
            {
                if(tempLength < wordsCopy[j-gap].length())
                {
                    swap(wordsCopy[j], wordsCopy[j-gap]);
                }
                else break;
                
            }
            
        }
    }
    for(gap = wordsSize/2; gap > 0; gap/= 2)
    {
        for(i = gap; i < wordsSize; ++i)
        {
            tempLength = wordsCopy[i].length();
            tempWord = wordsCopy[i];
            for(j = i; j >= gap; j-= gap)
            {
                if(tempLength == wordsCopy[j-gap].length())
                {
                    if(tempWord < wordsCopy[j-gap])
                    {
                        swap(wordsCopy[j], wordsCopy[j-gap]);
                    }
                    else break;
                }
            }
            
        }
    }

}


void SortingCompetition::outputData(const string& outputFileName)
{
    ofstream output(outputFileName);
    
    for (int i = 0; i < wordsSize; ++i)
    {
        cout << i << " " << wordsCopy[i] << " " << wordsCopy[i].size() << endl;

        output << wordsCopy[i] << endl;
    }
    
}


SortingCompetition::~SortingCompetition()
{
    delete [] wordsCopy;
    
}






