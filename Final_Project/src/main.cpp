//
//  main.cpp
//  Project_5
//
//

#include <iostream>
#include <string>

#include "SearchEngine.h"

int main()
{
    SearchEngine search("enwikibooks_main.xml");
    
    return search.start();
}