//
//  Indexer.cpp
//  Project_5
//
//

#include "Indexer.h"

Indexer::Indexer()
{
    avlind = new ag::avltree::AvlTree<string, vector<Page*>*>;
    mapind = new google::dense_hash_map<string, vector<Page*>*, hash<string>>;
    mapind->set_empty_key(string());
    stopwordlist = new StopWords("stop_words.txt");

    textParser = new TextProcessor(stopwordlist->get_list());
    duplicateCheck = new unordered_set<string>;
    
}


void Indexer::indexMap(Page * page)
{
    queue<string> *testq = textParser->process(page);
    page->set_TotalCount(testq->size());
    
    while (!testq->empty())
    {
        word = &testq->front();
        probe = duplicateCheck->find(*word);
        //Word Not In Structure
        if (mapind->operator[](*word) == NULL)
        {
            vector<Page*> *pageptr = new vector<Page*>;
            pageptr->push_back(page);
            duplicateCheck->insert(*word);
            mapind->operator[](testq->front()) = pageptr;
            page->addWord(*word);
        }
        //Duplicate on Current Page
        else if (probe != duplicateCheck->end())
        {
            page->addWord(*word);
        }
        //Different Page, Word In Structure
        else
        {
            vector<Page*> *pageList = mapind->operator[](*word);
            pageList->push_back(page);
            duplicateCheck->insert(*word);
            page->addWord(*word);
        }
        
        testq->pop();
    }
    
    duplicateCheck->clear();
}


void Indexer::indexAvl(Page* page)
{
    queue<string> *testq =  textParser->process(page);
    page->set_TotalCount(testq->size());
    
    while (!testq->empty())
    {
        word = &testq->front();
        probe = duplicateCheck->find(*word);

        if (avlind->get(*word) == NULL)
        {
            vector<Page*> *pageptr = new vector<Page*>;
            pageptr->push_back(page);
            duplicateCheck->insert(*word);
            avlind->put(testq->front(), pageptr);
            page->addWord(*word);
        }
        else if (probe != duplicateCheck->end())
        {
            page->addWord(*word);
        }
        else
        {
            vector<Page*> *pageList = avlind->get(*word);
            pageList->push_back(page);
            duplicateCheck->insert(*word);
            page->addWord(*word);
        }

        testq->pop();
    }
    
    duplicateCheck->clear();
}


void Indexer::clearIndices()
{
    mapind->clear();
    delete avlind;
    avlind = new ag::avltree::AvlTree<string, vector<Page*>*>;
}


vector<Page*> Indexer::getListOfPages(int structure, string search)
{
    //Map - 0
    if(structure == 0)
    {
        if (mapind->operator[](search) == NULL)
        {
            return emptyVector;
        }
        else
            return *mapind->operator[](search);
    }
    //Avl - 1
    else if (structure == 1)
    {
        if (avlind->get(search) == NULL)
        {
            return emptyVector;
        }
        else
            return *avlind->get(search);
    }
    
    return emptyVector;
}


Indexer::~Indexer()
{
    delete avlind;
    delete mapind;
    delete stopwordlist;
    delete textParser;
    delete duplicateCheck;
}

