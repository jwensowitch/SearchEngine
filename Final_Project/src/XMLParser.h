//
//  XMLParser.h
//  Project_5
//
//

#ifndef __Project_5__XMLParser__
#define __Project_5__XMLParser__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <stack>

#include "Page.h"
#include "/usr/local/Cellar/pugixml-1.4/src/pugixml.hpp"

using namespace std;

//!  XMLParser Class
/*!
A class that takes an xml and turns it into a queue of Page* to be processed.
 */


class XMLParser
{
    
private:
    string file;
    ifstream fileStream;
    pugi::xml_document doc;
    pugi::xml_parse_result parseResult;
    pugi::xml_node pageCrawler;
    vector<Page> *pages;
    queue<Page*> *quePages;
    
public:
    //!  XMLParser Constructor
    /*!
     Built from an .xml input file
     */
    XMLParser(std::string inputfile);
    //!  XMLParser Destructor
    ~XMLParser();
    /*!
     Initialize document parsing
     */
    void parseXML();
    /*!
     returns queue of Page* to be processed
     */
    queue<Page*> getQueue();
    
};


#endif /* defined(__Project_5__XMLParser__) */
