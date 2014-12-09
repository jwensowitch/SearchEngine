//
//  Page.cpp
//  Project_5
//
//

#include "Page.h"

Page::Page(int _uid, string _title, string _username, string _date, string _text):
uid(_uid),title(_title), username(_username), date(_date), text(_text)
{
    totalWordCount = 0;
}


void Page::set_TotalCount(size_t c)
{
    totalWordCount = c;
}


void Page::addWord(string s)
{
    if(indvCount.count(s) == 0)
    {
        indvCount.insert({s,1});
    }
    else
    {
        ++indvCount.operator[](s);
    }
}


size_t Page::getCount(string s)
{
    return indvCount.operator[](s);
}


int* Page::get_uid()
{
    return &uid;
}


string* Page::get_title()
{
    return &title;
}


string* Page::get_username()
{
    return &username;
}


string* Page::get_date()
{
    return &date;
}


string* Page::get_text()
{
    return &text;
}

Page::~Page()
{
    
}
