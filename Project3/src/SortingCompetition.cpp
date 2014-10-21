//
//  SortingCompetition.h
//  Wensowitch_Project3
//
//  Partner: Eric Hawkins
//
//**Output is outputing ascii values only not words

#include "SortingCompetition.h"

int shortcmp(const short* s1, const short* s2);

SortingCompetition :: SortingCompetition(const std :: string& inputFileName)
{
    input.open(inputFileName);
}

void SortingCompetition :: setFileName(const std :: string& inputFileName)
{
    input.open(inputFileName);
}

bool SortingCompetition :: readData()
{
    std :: string tempWords = "";
    short* tempShorts;
    bool specialChar;
    
    if(!input.is_open())
    {
        std :: cerr << "File Could Not Be Opened." << std :: endl;
        return 0;
    }
    else
    {
        words.clear();
        specialWords.clear();
        
        while (input >> tempWords)
        {
            specialChar = false;
            tempShorts = new short[tempWords.length() + 1];
            tempShorts[0] = tempWords.length();
            for(unsigned int i = 1; i <= tempWords.length(); ++i)
            {
                if((short)tempWords[i - 1] > 32 && (short)tempWords[i - 1] < 132 && (short)tempWords[i - 1] != 127)
                    tempShorts[i] = (short)tempWords[i - 1];
                else if((short)tempWords[i - 1] > 32 && (short)tempWords[i - 1] != 127)
                {
                    tempShorts[i] = (short)tempWords[i - 1];
                    specialChar = true;
                }
            }
            if(!specialChar)
                words.push_back(tempShorts);
            else
                specialWords.push_back(tempShorts);
            
        }
    }
    
    wordsSize = words.size();
    specWordsSize = specialWords.size();
    
    sumArr = new unsigned int*[wordsSize];
    lenArr = new unsigned int[wordsSize];
    numInts = new unsigned int[wordsSize];
    
    for(size_t i = 0; i < wordsSize; ++i)
    {
        if(i == 10)
        {
            //std :: cout << 'j';
        }
        lenArr[i] = words[i][0];
        if(lenArr[i] % 4 == 0)
        {
            numInts[i] = lenArr[i] / 4;
            sumArr[i] = new unsigned int[numInts[i]]();
        }
        else
        {
            numInts[i] = (lenArr[i] / 4) + 1;
            sumArr[i] = new unsigned int[numInts[i]]();
        }
        
        unsigned short j = 0, a = 1, b;
        while(true)
        {
            if(a + 3 >= lenArr[i])
            {
                b = lenArr[i];
                for(; b >= a; --b)
                {
                    sumArr[i][j] += pow(100, lenArr[i] - b) * (words[i][b] - 32);
                }
                break;
            }
            else
                for(b = a + 3; b >= a; --b)
                {
                    sumArr[i][j] += pow(100, a + 3 - b) * (words[i][b] - 32);
                }
            ++j;
            a += 4;
        }
        
    }
    
    input.close();
    
    indexes = new size_t[wordsSize];
    for(size_t i = 0; i < wordsSize; ++i)
        indexes[i] = i;
    
    return 1;
}


bool SortingCompetition :: prepareData()
{
    indexArr = new size_t[wordsSize];
    for(size_t i = 0; i < wordsSize; ++i)
    {
        indexArr[i] = indexes[i];
    }
    return 1;
}

void SortingCompetition :: sortData()
{
    //size_t arrayCounter = 0;
    array1_4 = new unsigned int[95959596]();

    
    swapIndex = wordsSize - 1;
    
    
    for(size_t i = wordsSize - 1; i > 0; --i)
    {
        if(lenArr[i] < 5)
        {
            ++array1_4[sumArr[i][0]];
        }
        else
        {
            indexArr[swapIndex] = i;
            --swapIndex;
        }
    }
    
    quickSort(swapIndex + 1, wordsSize - 1);
    
    //shellSort would be called with these same arguments in place of insertionSort.
    insertionSort(swapIndex + 1, wordsSize - 1);
    
    
}


void SortingCompetition :: gapSort(size_t l, size_t r)
{
    size_t size = r-l, i, j, gap, temp;
    for (gap = size/2; gap > 0; gap /= 2)
    {
        for(i = gap; i < size; ++i)
        {
            temp = indexArr[i];
            for (j = i; j >= gap; j -= gap)
            {
                if(sumArr[indexArr[j - gap]] < sumArr[temp])
                {
                    std::swap(indexArr[temp], indexArr[j-gap]);
                }
                else break;
            }
        }
    }
    
}



void SortingCompetition:: medianOfThree(size_t l, size_t r)
{
    size_t center = (l + r)/2;
    if ( sumArr[center] < sumArr[l] )
    {
        std :: swap(sumArr[l], sumArr[center]);
        std :: swap(lenArr[l], lenArr[center]);
        std :: swap(indexArr[l], indexArr[center]);
    }
    if ( sumArr[r] < sumArr[l] )
    {
        std :: swap(sumArr[l], sumArr[r]);
        std :: swap(lenArr[l], lenArr[r]);
        std :: swap(indexArr[l], indexArr[r]);
    }
    if ( sumArr[r] < sumArr[center] )
    {
        std :: swap(sumArr[r], sumArr[center]);
        std :: swap(lenArr[r], lenArr[center]);
        std :: swap(indexArr[r], indexArr[center]);
    }
    
}



void SortingCompetition :: quickSortA(size_t l, size_t r)
{
    ++recurs;
    size_t i, j;
    if((r - l) > 4)
    {
        i = (r + l) / 2;
        if(intcmp(sumArr[l], sumArr[i], l, i) > 0)
        {
            std :: swap(sumArr[l], sumArr[i]);
            std :: swap(lenArr[l], lenArr[i]);
            std :: swap(numInts[l], numInts[i]);
        }
        if(intcmp(sumArr[l], sumArr[r], l, r) > 0)
        {
            std :: swap(sumArr[l], sumArr[r]);
            std :: swap(lenArr[l], lenArr[r]);
            std :: swap(numInts[l], numInts[r]);
        }
        if(intcmp(sumArr[i], sumArr[r], i, r) > 0)
        {
            std :: swap(sumArr[i], sumArr[r]);
            std :: swap(lenArr[i], lenArr[r]);
            std :: swap(numInts[i], numInts[r]);
        }
        
        j = r;
        std :: swap(sumArr[i], sumArr[j]);
        std :: swap(lenArr[i], lenArr[j]);
        std :: swap(numInts[i], numInts[j]);
        i = l;
        
        unsigned int* temp = new unsigned int[lenArr[j]];
        for(int k = 0; k < lenArr[j]; ++k)
            temp[k] = sumArr[j][k];
        size_t q = j;
        while(true)
        {
            do
                ++i;
            while(intcmp(sumArr[i], temp, i, q) < 0);
            
            do
                --j;
            while(intcmp(sumArr[j], temp, j, q) > 0);
            
            if(j < i)
                break;
            std :: swap(sumArr[i], sumArr[j]);
            std :: swap(lenArr[i], lenArr[j]);
            std :: swap(numInts[i], numInts[j]);
        }
        
        delete[] temp;
        
        std :: swap(sumArr[i], sumArr[r]);
        std :: swap(lenArr[i], lenArr[r]);
        std :: swap(numInts[i], numInts[r]);
        quickSort(l, j);
        quickSort(i + 1, r);
        
    }
}

void SortingCompetition :: quickSort(size_t l, size_t r)
{
    size_t i, j;
    if((r - l) > 4)
    {
        i = (r + l) / 2;
        std::cout << indexArr[i] << std::endl;
        if(intcmp(sumArr[indexArr[l]], sumArr[indexArr[i]], indexArr[l], indexArr[i]) > 0)
        {
            std :: swap(indexArr[l], indexArr[i]);
        }
        if(intcmp(sumArr[indexArr[l]], sumArr[indexArr[r]], indexArr[l], indexArr[r]) > 0)
        {
            std :: swap(indexArr[l], indexArr[r]);
        }
        if(intcmp(sumArr[indexArr[i]], sumArr[indexArr[r]], indexArr[i], indexArr[r]) > 0)
        {
            std :: swap(indexArr[i], indexArr[r]);
        }
        
        j = r - 1;
        std :: swap(indexArr[i], indexArr[j]);
        i = l;
        
        size_t jHold = j;
        while(true)
        {
            do
            {
                ++i;
            }
            while(intcmp(sumArr[indexArr[i]], sumArr[indexArr[jHold]], indexArr[i], indexArr[jHold]) < 0);
            
            do
            {
                --j;
            }
            while(intcmp(sumArr[indexArr[j]], sumArr[indexArr[jHold]], indexArr[j], indexArr[jHold]) > 0);
            
            if(j < i)
                break;
            std :: swap(indexArr[i], indexArr[j]);
        }
        
        std :: swap(indexArr[i], indexArr[r - 1]);
        
        quickSort(l, j);
        quickSort(i + 1, r);
        
    }
}

void SortingCompetition :: insertionSort(unsigned int lo, unsigned int hi)
{
    unsigned int i, j, hold;
    for(i = lo + 1; i <= hi; ++i)
    {
        hold = indexArr[i];
        j = i;
        while(j > lo)
        {
            if(intcmp(sumArr[indexArr[j - 1]], sumArr[hold], indexArr[j - 1], hold) <= 0)
                break;
            
            indexArr[j] = indexArr[j - 1];
            --j;
        }
        indexArr[j] = hold;
    }
    
}


 //Compare two unsigned int arrays s1 and s2,
 //whose values in indexArr are a and b, respectively.
 //If s1 > s2, return 1.
 //If s1 < s2, return -1.
 //If s1 == s2, return 0.

int SortingCompetition :: intcmp(unsigned int* s1,  unsigned int* s2, size_t a, size_t b)
{
    if(lenArr[a] == lenArr[b])
    {
        if(s1[0] > s2[0])
            return 1;
        else if(s1[0] < s2[0])
            return -1;
        else if(s1[1] < s2[1])
            return 1;
        else if(s1[1] > s2[1])
            return -1;
        else if(s1[2] < s2[2])
            return 1;
        else if(s1[2] > s2[2])
            return -1;
        for(int i = 3; i < numInts[a]; ++i)
        {
            if(s1[i] > s2[i])
                return 1;
            else if(s1[i] < s2[i])
                return -1;
        }
        return 0;
    }
    else
    {
        if(lenArr[a] > lenArr[b])
            return 1;
        else if(lenArr[a] < lenArr[b])
            return -1;
        
    }
    
    return 0;
    
}


void SortingCompetition :: outputData(const std :: string& outputFileName)
{
    std :: ofstream outStream(outputFileName);
    std :: string word;
    

    for(size_t i = swapIndex + 1; i < wordsSize; ++i)
    {
        for(int j = 0; j < numInts[indexArr[i]]; ++j)
        {
            if(sumArr[indexArr[i]][j] > 9999 && sumArr[indexArr[i]][j] < 100000)
                outStream << '0' << sumArr[indexArr[i]][j];
            else if(sumArr[indexArr[i]][j] > 99 && sumArr[indexArr[i]][j] < 1000)
                outStream << '0' << sumArr[indexArr[i]][j];
            else if(sumArr[indexArr[i]][j] > 0 && sumArr[indexArr[i]][j] < 10)
                outStream << '0' << sumArr[indexArr[i]][j];
            else if(sumArr[indexArr[i]][j] > 999999 && sumArr[indexArr[i]][j] < 10000000)
                outStream << '0' << sumArr[indexArr[i]][j];
            else
                outStream << sumArr[indexArr[i]][j];
        }
        
        outStream << std :: endl;
    }
    
    outStream.close();
    
    std :: ofstream outStream2("output1_4.txt");
    for(unsigned i = 0; i < 94949495; ++i)
    {
        if(array1_4[i] > 0)
        {
            if(i > 9999 && i < 100000)
            {
                outStream2 << '0' << i << ": " << array1_4[i] << std :: endl;
            }
            else if(i > 99 && i < 1000)
            {
                outStream2 << '0' << i << ": " << array1_4[i] << std :: endl;
            }
            else if(i > 0 && i < 10)
            {
                outStream2 << '0' << i << ": " << array1_4[i] << std :: endl;
            }
            else if(i > 999999 && i < 10000000)
            {
                outStream2 << '0' << i << ": " << array1_4[i] << std :: endl;
            }
            else
            {
                outStream2 << i << ": " << array1_4[i] << std :: endl;
            }
        }
    }
    
    outStream2.close();
    
}

size_t SortingCompetition :: getWordsSize()
{ return wordsSize; }

void SortingCompetition :: printData()
{
    int jorge = 0, julio = 0;
    for(size_t i = 0; sumArr[i][0] != 0; i++)
    {
  
        jorge++;
       
    }
    std :: cout << jorge << " total\n";
    std :: cout << julio << " words processed\n";
}


SortingCompetition :: ~SortingCompetition()
{
    delete[] array1_4;
    //delete[] array5;
    for(unsigned int i = 0; i < wordsSize; i++)
        delete[] sumArr[i];
    delete[] sumArr;
    delete[] numInts;
    delete[] lenArr;
    delete[] indexes;
    delete[] indexArr;
    delete[] tempShorts;
    
}
