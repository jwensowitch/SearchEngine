//
//  XMLParser.cpp
//  Project_5
//
//

#include "XMLParser.h"

XMLParser::XMLParser(std::string inputfile) : file(inputfile)
{
    fileStream.open(file);
    parseResult = doc.load(fileStream);
    pageCrawler = doc.child("mediawiki").child("page");
    
    pages = new vector<Page>;
    quePages = new queue<Page*>;
}


void XMLParser::parseXML()
{
    for(pugi::xml_node tool = pageCrawler; tool; tool = tool.next_sibling())
    {
        Page *t = new Page(tool.child("id").text().as_int(),
                           tool.child("title").text().as_string(),
                           tool.child("revision").child("contributor").child("username").text().as_string(),
                           tool.child("revision").child("timestamp").text().as_string(),
                           tool.child("revision").child("text").text().as_string() );

        pages->push_back(*t);
        quePages->push(t);
    }
    
    fileStream.close();
}


queue<Page*> XMLParser::getQueue()
{
    return *quePages;
}


XMLParser::~XMLParser()
{
    delete pages;
    delete quePages;
}

