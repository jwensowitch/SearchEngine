//
//  TextProcessor.cpp
//  Project_5
//
//

#include "TextProcessor.h"

TextProcessor::TextProcessor(unordered_set<string>* _uos_stopWords):
    uos_stopWords(_uos_stopWords)
{
    queKeyWords = new queue<string>;
}


queue<string>* TextProcessor::process(Page* page)
{
    //Page of Raw Text
    string *text = page->get_text();
    
    //Basic removal of HTML Elements
    stripHTMLTags(text);
    
    //Lowercase
    transform(text->begin(), text->end(), text->begin(), ::tolower);
    
    boost::tokenizer<> pager(text);
    unordered_set<string>::const_iterator probe;
    for(boost::tokenizer<>::iterator it=pager.begin(); it!=pager.end(); ++it)
    {
        //Probe for Stop Words
        probe = uos_stopWords->find(*it);
        
        s = new string;
        *s = (string)(*it);
        
        //Add to Queue: length > 2 & Not a Stop Word
        if(probe == uos_stopWords->end() && it->length() > 2)
        {
            Porter2Stemmer::stem(*s);
            queKeyWords->push(*s);
        }
        
        delete s;
        
    }

    return queKeyWords;
}


TextProcessor::~TextProcessor()
{
    delete queKeyWords;
}

//HTMLStripper: http://www.linuxtopia.org/online_books/programming_books/c++_practical_programming/c++_practical_programming_065.html
string* TextProcessor::stripHTMLTags(string* s)
{
    size_t leftPos;
    size_t lt, gt;
    char l = '<';
    char g = '>';
    
    replaceAll(s, "&amp;", "&");
    replaceAll(s, "&lt;", "<");
    replaceAll(s, "&gt;", ">");
    replaceAll(s, "&nbsp;", " ");
    replaceAll(s, "{", "<");
    replaceAll(s, "}", ">");
    
    lt = count(s->begin(), s->end(), l);
    gt = count(s->begin(), s->end(), g);
    
    if(lt < gt)
    {
        while((leftPos = s->find('<')) != string::npos)
        {
            size_t rightPos = s->find('>', leftPos+1);
            s->erase(leftPos, rightPos-leftPos + 1);
        }
        
    }
    
    return s;
}

