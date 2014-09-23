//
//  main.cpp
//  project2
//  John Wensowitch
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <cmath>
#include <math.h>

using namespace std;

void resizeChar(char**&, int&);
void resizePages(int**&, int&, int*&, int*&);
void resizePageRow(int**&, int*, int);

void lowercase(char*&);
bool duplicateWord(char**&, char*&, int&, int&);

void sortPageRows(int**&, int*&, int);
void sortWords(char**, int**, int*, int*, int);

int main(int argc, char* argv[])
{
    int size_words = 0;
    int size_pages = 0;
    const int int_cap_words = 10;
    const int int_cap_pages = 10;
    int cap_words = int_cap_words;
    int cap_pages = int_cap_pages;
    int buffer_size = 81;
    int currentPage = 0;
    
    
    char** words = new char*[int_cap_words];
    int** pages = new int*[int_cap_pages];
    
    char* buffer = new char[buffer_size];
    char* bufferW = new char[buffer_size];
    char* bufferP = new char[buffer_size];
    int* pagesColCount = new int[int_cap_pages];
    int* pagesRowCapacity = new int[int_cap_pages];
    
    char peekerWords;
    
    //Instantiation of Dynamic Arrays
    for(int i = 0; i < cap_pages; ++i)
    {
        pages[i] = new int[cap_pages];
    }
    
    for(int i = 0; i < cap_pages; ++i)
    {
        pagesColCount[i] = 0;
        pagesRowCapacity[i] = 10;
        for(int j = 0; j < cap_pages; ++j)
        {
            pages[i][j] = 0;
        }
        
    }
    
    ifstream inFile(argv[1]);
    
    if(!inFile)
    {
        cerr << "File could not be opened" << endl;
        
        return 1;
    }
    
    //Input//
    
    stringstream wordStream, pageStream;
    
    char firstChar = ' ', lastChar = ' ';
    int lastCharInd = 0;
    int pageIndex = 0;
    int lastInd = 0;
    
    while(!inFile.eof())
    {
        firstChar = inFile.peek();
        
        if(firstChar == '<')
        {
            inFile.ignore(1, '<');
            inFile.getline(buffer, buffer_size);
            
            pageStream << buffer;
            
            pageStream.getline(bufferP, 10, '>');
            pageStream.clear();
            
            currentPage = atoi(bufferP);
        }
        else
        {
            inFile.getline(buffer, buffer_size);
            wordStream << buffer;
            
            while(lastChar != '\0' && lastChar != '\n')
            {
                peekerWords = wordStream.peek();
                
                if(peekerWords == 91)  // '[' = 91
                {
                    wordStream.ignore();
                    wordStream.getline(bufferW, buffer_size , ']');
                    wordStream.ignore();
                    
                    if(lastCharInd == 0)
                    {
                        lastCharInd += strlen(bufferW) + 2; //no preceding space
                    }
                    else
                    {
                        lastCharInd += strlen(bufferW) + 3; //accounts for preceding space '[' & ']'
                    }
                    
                }
                else
                {
                    wordStream.getline(bufferW, buffer_size, ' ');
                    
                    if(lastCharInd == 0){
                        lastCharInd += strlen(bufferW); //no preceding space
                    }
                    else
                    {
                        lastCharInd += strlen(bufferW) + 1; //accounts for preceding space
                    }
                    
                }
                
                lastChar = buffer[lastCharInd];
                
                lowercase(bufferW);
                
                if(duplicateWord(words, bufferW, lastInd, pageIndex))
                {
                    pages[pageIndex][pagesColCount[pageIndex]] = currentPage;   //pageIndex updated in duplicateWord() for
                    //    adding page numbers to proper index
                    ++pagesColCount[pageIndex];
                    //cout << pageIndex << ":" << pagesColCount[pageIndex] << " ";
                    //cout << bufferW << " is a duplicate at " << lastInd << endl;
                    
                    if(pagesColCount[pageIndex] >= pagesRowCapacity[pageIndex]) //if the individual row that was
                    {                                                           //  just added to has reached
                        resizePageRow(pages, pagesRowCapacity, pageIndex);      //  it's capacity -> resize that row
                    }
                    
                }
                else
                {
                    words[lastInd] = new char[strlen(bufferW) + 1]; //dynamic word length addition
                    ++size_words;                                   // to array (+1 for '\0')
                    
                    pages[lastInd][0] = currentPage;
                    ++size_pages;
                    
                    ++pagesColCount[lastInd];
                    strcpy(words[lastInd], bufferW);
                    ++lastInd;
                }
                
                if(lastInd >= cap_words)
                {
                    resizePages(pages, cap_pages, pagesRowCapacity, pagesColCount);
                    resizeChar(words, cap_words);
                    
                }
                
                
                
            }
            
            wordStream.clear();
            lastChar = ' ';
            lastCharInd = 0;
        }
        
    }
    
    inFile.close();
    
    delete[] buffer;
    delete[] bufferW;
    delete[] bufferP;
    
    sortPageRows(pages, pagesColCount, lastInd);
    sortWords(words, pages, pagesRowCapacity, pagesColCount, lastInd);
    
    
    //Output//
    
    ofstream outFile(argv[2]);
    
    int index = 0;
    int numLength = 0;
    int wordLength = 0;
    int otherCharCount = 0;
    char currentLetter = ' ';
    bool indent = false;
    
    for(index = 0; index < lastInd;)
    {
        currentLetter = words[index][0];
        
        outFile << "[" << (char)toupper(currentLetter) << "]" << endl;
        
        while(currentLetter == words[index][0]) {
            
            outFile << words[index] << ":";
            otherCharCount += 1;
            wordLength = (int)strlen(words[index]);
            
            for(int j = 0; j < pagesColCount[index]; ++j)
            {
                if((numLength + wordLength + otherCharCount) >= 50 && !indent ){
                    outFile << "\n" << "    ";
                    indent = true;
                }
                if(pages[index][j] != pages[index][j+1])
                {
                    numLength += (pages[index][j] ==0) ? 1 : (int)log10(pages[index][j]) + 1;
                    outFile << " " << pages[index][j];
                    otherCharCount += 1;
                    if(pagesColCount[index] > 1 && j < pagesColCount[index] - 1)
                    {
                        outFile << ",";
                        otherCharCount += 1;
                    }
                    
                }
                
            }
            
            indent = false;
            outFile << endl;
            
            numLength = 0;
            wordLength = 0;
            otherCharCount = 0;
            ++index;
            
            if(index == lastInd)
            {
                break;
            }
            
        }
        
    }
    
    outFile.close();
    
    for(int i = 0; i < lastInd; ++i) {
        delete[] words[i];
        delete[] pages[i];
    }
    
    
    delete[] pages;
    delete[] words;
    delete[] pagesColCount;
    delete[] pagesRowCapacity;
    
    
    return 0;
}


void resizePageRow(int**& pages, int* capacity, int row)
{
    int* tempPages = new int[capacity[row] + 10];
    
    for(int i = 0; i < capacity[row]; ++i)
    {
        tempPages[i] = pages[row][i];
    }
    
    delete[] pages[row];
    
    for(int i = capacity[row]; i < capacity[row] + 10; ++i)
    {
        tempPages[i] = 0;
    }
    
    pages[row] = tempPages;
    
    capacity[row] += 10;
    
}

void resizePages(int**& pages, int& capacity, int*& rowCapacity, int*& colCount)
{
    int** tempPages = new int*[capacity + 10];
    int* tempColCount = new int[capacity + 10];
    int* tempRowCap = new int[capacity + 10];
    
    //Copy existing values
    for(int i = 0; i < capacity; ++i)
    {
        
        tempPages[i] = new int[rowCapacity[i]];
        tempColCount[i] = colCount[i];
        tempRowCap[i] = rowCapacity[i];
        
        for(int j = 0; j < colCount[i]; ++j)
        {
            tempPages[i][j] = pages[i][j];
        }
        
    }
    
    //Instantiate new values and spaces
    for(int i = capacity; i < capacity + 10; ++i)
    {
        tempPages[i] = new int[10];
        tempColCount[i] = 0;
        tempRowCap[i] = 10;
        
        for(int j = tempColCount[i]; j < tempRowCap[i]; ++j)
        {
            tempPages[i][j] = 0;
        }
    }
    
    for(int i = 0; i < capacity; ++i)
    {
        delete[] pages[i];
    }
    
    delete[] rowCapacity;
    delete[] colCount;
    delete[] pages;
    rowCapacity = tempRowCap;
    pages = tempPages;
    colCount = tempColCount;
    
    capacity+=10;
    
}

//Selection sort by pointers
void sortWords(char **words, int **pages, int* rowCap, int* colCount, int indexCount)
{
	for (int i = 0; i <indexCount-1; ++i)
    {
		int min = i;
		for (int j = i + 1; j < indexCount; ++j)
        {
			if( (strcmp(words[j], words[min])) < 0)
            {
				min = j;
			}
		}
		if (min != i)
        {
            int* tempPages = pages[i];
			char* tempWords = words[i];
            int tempColCount = colCount[i];
            int tempRow = rowCap[i];
            pages[i] = pages[min];
			words[i] = words[min];
            colCount[i] = colCount[min];
            rowCap[i] =rowCap[min];
			pages[min] = tempPages;
            words[min] = tempWords;
            colCount[min] = tempColCount;
            rowCap[min] = tempRow;
            
		}
	}
}


void sortPageRows(int**& pages, int*& colCount, int indexCount)
{
    int i, j, k, tempPage;
    for(i = 0; i < indexCount; ++i)
    {
        for(j = 0; j < colCount[i]; ++j)
        {
            for(k = j+1; k < colCount[i]; ++k)
            {
                if(pages[i][k] < pages[i][j])
                {
                    tempPage = pages[i][j];
                    pages[i][j] = pages[i][k];
                    pages[i][k] = tempPage;
                }
            }
        }
    }
}


void resizeChar(char**& words, int& capacity)
{
    char** tempWords = new char*[capacity + 10];
    for(int i = 0; i < capacity ; ++i)
    {
        tempWords[i] = new char[strlen(words[i])];
        strcpy(tempWords[i], words[i]);
        delete[] words[i];
    }
    
    delete[] words;
    words = tempWords;
    capacity+=10;
}


void lowercase(char*& ch)
{
    size_t size = strlen(ch);
    for(size_t i = 0; i < size; ++i)
    {
        ch[i] = tolower(ch[i]);
    }
}


bool duplicateWord(char**& words, char*& currentWord, int& indSize, int& pgInd)
{
    for(int i = 0; i < indSize; ++i)
    {
        if(!strcmp(words[i], currentWord))
        {
            pgInd = i;  //sets by reference the pageIndex where duplicate is found
            
            return 1;
        }
        
    }
    
    return 0;
}

