//
//  QueryProcessor.cpp
//  Project_5
//
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(Indexer * _index) : index(_index)
{
    rawResults = new vector<vector<Page*> >;
    processedResults = new vector<Page*>;
    relevancy = new vector<int>(1,0);
    stopwordlist = new StopWords("query_stop_words.txt");
    stopWords = stopwordlist->get_list();
}


vector<Page*>* QueryProcessor::process(int structure, string search)
{
    bool is_not = false;
    int not_pos = 0;
    unsigned long length = 0;
    vector<Page*> hold;
    unordered_set<string>::const_iterator probe;
    
    istringstream searchStream(search);
    
    vector<string> tokens{istream_iterator<string>{searchStream},
        istream_iterator<string>{}};
    
    //Clear Results(reusable funct.)
    processedResults->clear();
    rawResults->clear();

    //Remove Stop Words
    for (int i = 0; i < tokens.size(); ++i)
    {
        probe = stopWords->find(tokens[i]);
        if(probe != stopWords->end())
        {
            tokens.erase(tokens.begin()+i);
        }
    }
    
    //Checking for NOT, Lowercase, & Stem
    for (int i = 0; i < tokens.size(); ++i)
    {
        //cout << tokens[i] << endl;
        if (tokens[i] == "NOT")
        {
            is_not = true;
            not_pos = i;
        }
        
        transform(tokens[i].begin(), tokens[i].end(),
                  tokens[i].begin(), ::tolower);
        
        Porter2Stemmer::stem(tokens[i]);
        
    }
    
    //Length of Search Terms
    if(is_not)
    {
        length = tokens.size() - (tokens.size()-not_pos) - 1;
    }
    else if (tokens.size() > 1)
    {
        length = tokens.size()-1;
    }
    else if (tokens.size() == 1)
    {
        length = 0;
        rawResults->push_back(index->getListOfPages(structure, tokens[0]));
    }
    
    //Length > 0, add to results
    for(int i = 0; i < length; ++i)
    {
        rawResults->push_back(index->getListOfPages(structure, tokens[i+1]));
    }
    
    //Single Search Term
    if(length == 0)
    {
        rawResults->push_back(index->getListOfPages(structure, tokens[0]));
        length = 1;
    }
    
    //AND...
    if( (tokens[0].compare("AND") == 0 || tokens[0].compare("and") == 0)
       && length >= 2 )
    {
        size_t size = 0;
        vector<Page*> temp;
        
        set_intersection(rawResults->operator[](0).begin(), rawResults->operator[](0).end(),
                         rawResults->operator[](1).begin(), rawResults->operator[](1).end(),
                         back_inserter(temp));
        
        if(length > 2)
        {
            for (int i = 2; i < length; ++i)
            {
                size = temp.size();
                
                set_intersection(temp.begin(), temp.end(),
                                 rawResults->operator[](i).begin(), rawResults->operator[](i).end(),
                                 back_inserter(temp));
                
                vector<Page*> vec(temp.begin()+size, temp.begin()+temp.size());
                
                sort(temp.begin(), temp.end());
                
                *processedResults = vec;
            }
        }
        else if(length == 2)
        {
            *processedResults = temp;
        }
        
    }
    //OR...
    else if(( tokens[0].compare("OR") == 0 || tokens[0].compare("or") == 0 ) && length >= 2)
    {
        vector<Page*> temp = rawResults->operator[](0);
        for (int i = 1; i < length; ++i)
        {
            temp = merge_copy(temp, rawResults->operator[](i));
            sort( temp.begin(), temp.end() );
            temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
            
        }
        
        *processedResults = temp;
        
    }
    //Single Term
    else
    {
        *processedResults = rawResults->operator[](0);
    }
    
    //NOT...
    if(is_not && tokens.size() >= 3)
    {
        size_t size = 0;
        int notLength = 0;
        vector<Page*> temp;
        
        for(int i = not_pos + 1; i < tokens.size(); ++i, ++notLength)
        {
            rawResults->push_back(index->getListOfPages(structure, tokens[i]));
        }
        
        set_difference(processedResults->begin(), processedResults->end(),
                       rawResults->operator[](length).begin(),
                       rawResults->operator[](length).end(),
                       back_inserter(temp) );
        
        if(notLength > 1)
        {
            for (int i = 1; i < notLength; ++i)
            {
                size = (size_t)temp.size();
                
                set_difference(temp.begin(), temp.end(),
                               rawResults->operator[](length+i).begin(),
                               rawResults->operator[](length+i).end(),
                               back_inserter(temp));
                
                vector<Page*> vec(temp.begin()+size, temp.begin()+temp.size());
                temp = vec;
                sort(temp.begin(), temp.end());
                
                *processedResults = vec;
            }
            
        }
        else
        {
            *processedResults = temp;
        }
        
    }
    
    //Calculate Relevancy
    relevancy->clear();
    relevancy->reserve(processedResults->size());
    
    for(int i = 0; i < processedResults->size(); ++i)
    {
        int temp = 0;
        
        if(tokens[0] == "and" || tokens[0] == "or")
        {
            for (int j = 0; j < length ; ++j)
            {
                temp += processedResults->operator[](i)->getCount(tokens[j+1]);
            }
            
        }
        else
        {
            temp += processedResults->operator[](i)->getCount(tokens[0]);
        }
        
        relevancy->operator[](i) = temp;
        
    }
    
    //Sorting Results(relevancy)
	int pos_min,temp;
    Page* temp2;
    
    if (processedResults->size() > 1)
    {
        //Selection Sort: http://cforbeginners.com/ssort.html
        for (int i=0; i < processedResults->size()-1; i++)
        {
            pos_min = i;//set pos_min to the current index of array
            
            for (int j=i+1; j < processedResults->size(); j++)
            {
                
                if (relevancy->operator[](j) > relevancy->operator[](pos_min))
                    pos_min=j;
                //pos_min will keep track of the index that min is in, this is needed when a swap happens
            }
            
            //if pos_min no longer equals i than a smaller value must have been found, so a swap must occur
            if (pos_min != i)
            {
                temp = relevancy->operator[](i);
                temp2 = processedResults->operator[](i);
                relevancy->operator[](i) = relevancy->operator[](pos_min);
                processedResults->operator[](i) = processedResults->operator[](pos_min);
                relevancy->operator[](pos_min) = temp;
                processedResults->operator[](pos_min) = temp2;
            }
            
        }
        
    }
    
    return processedResults;
}


vector<int>* QueryProcessor::getRelevancy()
{
    return relevancy;
}


QueryProcessor::~QueryProcessor()
{
    delete rawResults;
    delete processedResults;
    delete stopwordlist;
    delete relevancy;
}

 
vector<Page*> QueryProcessor::merge_copy(const vector<Page*>& a, const vector<Page*>& b)
{
    vector<Page*> ret(a);
    copy(b.begin(), b.end(), back_inserter(ret));
    return ret;
}



