//
//  SortingCompetition.cpp
//  Wensowitch_Project3
//

#include "SortingCompetition.h"

void mySwap(string&, string&);

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
    size_t i = 0, j = 0, k = 0, gap, tempLength;
    string tempWord;
    
    for(gap = 2*(wordsSize/pow(2,k+1)) + 1; gap > 0; ++k)
    {
        for(i = gap; i < wordsSize; ++i)
        {
            tempLength = wordsCopy[i].length();
            for(j = i; j >= gap; j-= gap)
            {
                if(tempLength < wordsCopy[j-gap].length())
                {
                    wordsCopy[j].swap(wordsCopy[j-gap]);
                }
                else break;
            }
        }
        
        gap = 2*(wordsSize/pow(2,k+1));
    }
    
    k = 0;
    
    for(gap = 2*(wordsSize/pow(2,k+1)) + 1; gap > 0; ++k)
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
                        wordsCopy[j].swap(wordsCopy[j-gap]);
                    }
                    else break;
                }
            }
        }
        gap = 2*(wordsSize/pow(2,k+1));
    }
     

}


void SortingCompetition::outputData(const string& outputFileName)
{
    ofstream output(outputFileName);
    
    for (int i = 0; i < wordsSize; ++i)
    {
        //cout << i << " " << wordsCopy[i] << " " << wordsCopy[i].size() << endl;

        output << wordsCopy[i] << endl;
    }
    
}


SortingCompetition::~SortingCompetition()
{
    delete [] wordsCopy;
    
}


void mySwap(string& a, string& b)   //save time of templated
{
    string c(move(a)); a = move(b); b=move(c);
}



