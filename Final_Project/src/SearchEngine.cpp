//
//  SearchEngine.cpp
//  Project_5
//
//  Created by Admin on 11/16/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine(string inputXML)
{
    pXml = new XMLParser(inputXML);
    index = new Indexer();
    rawPageQueue = new queue<Page*>;
    structure = -1;
}

void SearchEngine::parse()
{
    pXml->parseXML();
    *rawPageQueue = pXml->getQueue();
    delete pXml;
}

void SearchEngine::loadIndex()
{
    
    while (!rawPageQueue->empty())
    {
        index->indexMap(rawPageQueue->front());
        index->indexAvl(rawPageQueue->front());
        rawPageQueue->pop();
    }
    
    searchProcessor = new QueryProcessor(index);
    
}

void SearchEngine::timeIndex()
{
    std::chrono::time_point<std::chrono::system_clock> start, end, startWhole, endWhole;
    unsigned int milliseconds;
    
    string file;
    string indexFile;
    
    
    cout << "Enter File Name:";
    cin >> file;
    ifstream infile(file);
    while (!infile)
    {
        cout << "Does Not Exist, Try Again\nEnter File Name:";
        cin >> file;
    }
    infile.close();

    index->clearIndices();

    XMLParser *newDocs = new XMLParser(file);
    newDocs->parseXML();
    *rawPageQueue = newDocs->getQueue();
    
    startWhole = std::chrono::system_clock::now();
    while (!rawPageQueue->empty())
    {
        index->indexMap(rawPageQueue->front());
        rawPageQueue->pop();
    }
    endWhole = std::chrono::system_clock::now();

    newDocs->parseXML();
    *rawPageQueue = newDocs->getQueue();
    
    start = std::chrono::system_clock::now();
    while (!rawPageQueue->empty())
    {
        index->indexAvl(rawPageQueue->front());
        rawPageQueue->pop();
    }
    end = std::chrono::system_clock::now();
    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << "Loading Hashmap index took: " << milliseconds << " milliseconds" << std::endl;
    unsigned int millisecondsWhole = std::chrono::duration_cast<std::chrono::milliseconds>(endWhole-startWhole).count();
    std::cout << "Loading Avl Tree index took: " << millisecondsWhole << " milliseconds" << std::endl;
    
}

void SearchEngine::clearLoad()
{
    std::chrono::time_point<std::chrono::system_clock> start, end, startWhole, endWhole;
    unsigned int milliseconds;

    string file;
    string indexFile;
    int runs;
    
    cout << "Enter File Name:";
    cin >> file;
    ifstream infile(file);
    while (!infile)
    {
        cout << "Does Not Exist, Try Again\nEnter File Name:";
        cin >> file;
        infile.open(file);
    }


    infile >> runs;
    infile.ignore();
    startWhole = std::chrono::system_clock::now();

    for (int i = 0; i < runs; ++i)
    {
        start = std::chrono::system_clock::now();
        index->clearIndices();
        getline(infile, indexFile);
        XMLParser *newDocs = new XMLParser(indexFile);
        newDocs->parseXML();
        *rawPageQueue = newDocs->getQueue();
        
        loadIndex();
        
        
        delete newDocs;
        end = std::chrono::system_clock::now();
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << "Doc " << i+1 << ":" << indexFile << " Time: " << milliseconds << " milliseconds" << std::endl;
        
    }
    endWhole = std::chrono::system_clock::now();
    unsigned int millisecondsWhole = std::chrono::duration_cast<std::chrono::milliseconds>(endWhole-startWhole).count();
    std::cout << "Clearing and loading " << runs << " indices took: " << millisecondsWhole << " milliseconds" << std::endl;
    
}


void SearchEngine::iterativeSearch()
{
    std::chrono::time_point<std::chrono::system_clock> start, end, startWhole, endWhole;
    unsigned int milliseconds;
    
    string file;
    string search, struc;
    int runs;
    
    cout << "Enter File Name:";
    cin >> file;
    ifstream infile(file);
    while (!infile)
    {
        cout << "Does Not Exist, Try Again\nEnter File Name:";
        cin >> file;
        infile.open(file);
    }
    
    cout << "\n1: Hash Map\n2: AVL Tree" << endl;
    cin >> struc;
    
    while (!is_number(struc) || (stoi(struc) < 1 && stoi(struc) > 2))
    {
        cout << "Invalid Selection, Try Again" << endl;
        cin >> struc;
    }
    
    
    infile >> runs;
    infile.ignore();
    startWhole = std::chrono::system_clock::now();

    for (int i = 0; i < runs; ++i)
    {
        start = std::chrono::system_clock::now();
        getline(infile, search);
        results = searchProcessor->process(stoi(struc)-1, search);
        cout << "Search:\"" << search << "\" Returned " << results->size() << " results" << " in: ";
        
        end = std::chrono::system_clock::now();
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << milliseconds << " milliseconds" << std::endl;
    }
    cout << endl;
    endWhole = std::chrono::system_clock::now();
    unsigned int millisecondsWhole = std::chrono::duration_cast<std::chrono::milliseconds>(endWhole-startWhole).count();
    std::cout << runs << " total searches took: " << millisecondsWhole << " milliseconds" << std::endl;
    
    
}


void SearchEngine::addDocs()
{
    string file;
    cout << "Enter File Name:";
    cin.ignore();
    cin >> file;
    ifstream infile(file);
    while (!infile)
    {
        cout << "Does Not Exist, Try Again\nEnter File Name:";
        cin >> file;
        infile.open(file);
    }
        
    XMLParser *newDocs = new XMLParser(file);
    newDocs->parseXML();
    *rawPageQueue = newDocs->getQueue();
    loadIndex();
    infile.close();
    delete newDocs;
    
}

void SearchEngine::search(int structure)
{
    int numResults;
    string search;
    string searchSelection;
    cout << "Search Term:";
    cin.ignore();
    getline(cin, search);
    results = searchProcessor->process(structure, search);
    vector<int> *relevancy = searchProcessor->getRelevancy();
    cout << results->size() << " results" << endl;
    if(results->size() == 0)
    {
        cout << "No Results\n" << endl;
        numResults = 0;
    }
    else
    {
        if(results->size() > 15)
        {
            numResults = 15;
        }
        else
        {
            numResults = results->size();
        }
        
        for(int i = 0; i < numResults; ++i)
        {
            cout << i+1 << "   " <<
            *results->operator[](i)->get_title() << '\n' << "    " <<
            *results->operator[](i)->get_date() << '\n' << "    " <<
            *results->operator[](i)->get_username() << '\n' << "    " <<
            "TF/IDF:" << relevancy->operator[](i) << endl << endl;
        }
        
        cout << "Selection\n---------\n0: Cancel Search\n1-" << numResults << ": Page Selection" << endl;
        cin >> searchSelection;
        if (searchSelection == "0")
        {
            return;
        }
        else if (is_number(searchSelection) && stoi(searchSelection) >= 1 && stoi(searchSelection) <= numResults)
        {
            cout << *results->operator[](stoi(searchSelection)-1)->get_title() << '\n' <<
            *results->operator[](stoi(searchSelection)-1)->get_date() << '\n' <<
            *results->operator[](stoi(searchSelection)-1)->get_username() << '\n' <<
            *results->operator[](stoi(searchSelection)-1)->get_text() << '\n' << endl;
        }
        else
        {
            cout << "Invalid Selction\n" << endl;
        }
    }
    
}


int SearchEngine::start()
{
    parse();
    loadIndex();
    
    string choice;
    cout << "Welcome to MustangWiki's Search Engine" << endl;
    cout << setfill('-') << setw(38) << '-'<< endl << endl;
    do
    {
        cout << "MAIN MENU\n1: Maintenance Mode\n2: Interactive Search\n3: Stress Test\n4: Quit" << endl;
        
        
        cin >> choice;
        
        while (!is_number(choice))
        {
            cout << "Invalid Selection, Try Again" << endl;
            cin >> choice;
        }
        
        switch (stoi(choice))
        {
            case 1:
                do
                {
                    cout << "MAINTENANCE MODE\n1: Add Documents\n2: Clear Index(added docs will need to be re-added)\n3: Go Back" << endl;
                    cin >> choice;
                    while (!is_number(choice))
                    {
                        cout << "Invalid Selection, Try Again" << endl;
                        cin >> choice;
                    }
                    if (stoi(choice) == 1)
                    {
                        addDocs();
                    }
                    else if(stoi(choice) == 2)
                    {
                        index->clearIndices();
                    }
                    else if (stoi(choice) == 3)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "Invalid Selection" << endl;
                    }
                    
                } while(stoi(choice) != 3);
                break;
                
            case 2:
                do
                {
                    cout << "INTERACTIVE SEARCH\n1: Search Hash Map\n2: Search AVL Tree\n3: Go Back" << endl;
                    cin >> choice;
                    while (!is_number(choice))
                    {
                        cout << "Invalid Selection, Try Again" << endl;
                        cin >> choice;
                    }
                    if (stoi(choice) == 1)
                    {
                        search(0);
                    }
                    else if (stoi(choice) == 2)
                    {
                        search(1);
                    }
                    else if(stoi(choice) == 3)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "Invalid Selection" << endl;
                    }
                } while(stoi(choice) != 3);
                break;
                
            case 3:
                do
                {
                    cout << "STRESS TEST\n1: Clear and Load Index\n2: Iterative Search Time\n3: Time to Index\n4: Go Back" << endl;
                    cin >> choice;
                    while (!is_number(choice))
                    {
                        cout << "Invalid Selection, Try Again" << endl;
                        cin >> choice;
                    }
                    if (stoi(choice) == 1)
                    {
                        clearLoad();
                    }
                    else if (stoi(choice) == 2)
                    {
                        iterativeSearch();
                    }
                    else if(stoi(choice) == 3)
                    {
                        timeIndex();
                    }
                    else if (stoi(choice) == 4)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "Invalid Selection" << endl;
                    }
                } while(stoi(choice) != 4);
                break;
                
            case 4:
                cout << "Are You Sure? Re-indexing Required!\n1: Quit\n2: Cancel" << endl;
                cin >> choice;
                while (!is_number(choice))
                {
                    cout << "Invalid Selection, Try Again" << endl;
                    cin >> choice;
                }
                if (stoi(choice) == 1)
                {
                    return 0;
                }
                else if (stoi(choice) == 2)
                {
                    continue;
                }
                else
                {
                    cout << "Invalid Selection" << endl;
                }
                break;
                
            default:
                cout << "Invalid Selection\n";
                break;
        }
        
    } while (true);
    
    return 0;
}

bool SearchEngine::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}


SearchEngine::~SearchEngine()
{
    delete index;
    delete rawPageQueue;

}


