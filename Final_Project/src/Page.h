//
//  Page.h
//  Project_5
//
//

#ifndef __Project_5__Page__
#define __Project_5__Page__

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

//!  Page class.
/*!
 A class that handles Page Object data.
 */

class Page
{
    
private:
    int uid;
    size_t totalWordCount;
    string title;
    string username;
    string date;
    string text;
    unordered_map<string, int> indvCount;
    
public:
    //!  Page Constructor.
    /*!
     Built from XMLParser relevant data.
     */
    Page(int _uid,
         string _title,
         string _username,
         string _date,
         string _text);
    //!  Page Destructor.
    ~Page();
    /*!
     Returns unique id of a page.
     */
    int* get_uid();
    /*!
     Returns the number of times a specific word appears on a page.
     */
    size_t getCount(string);
    /*!
     Returns the title of a page.
     */
    string* get_title();
    /*!
     Returns the username of the contributor of a page.
     */
    string* get_username();
    /*!
     Returns the date created of a page.
     */
    string* get_date();
    /*!
     Returns the textbody of a page.
     */
    string* get_text();
    /*!
     Sets the total count of word on a page. (TF/IDF)
     */
    void set_TotalCount(size_t);
    /*!
     Allows the count of specific words to be stored.
     */
    void addWord(string);
    
};


#endif /* defined(__Project_5__Page__) */
