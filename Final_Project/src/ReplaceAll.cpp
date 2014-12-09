//
//  ReplaceAll.cpp
//  Project_5
//
//  Created by Admin on 11/18/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#include "ReplaceAll.h"
using namespace std;

string* replaceAll(string* context, const string& from,
                   const string& to) {
    size_t lookHere = 0;
    size_t foundHere;
    while((foundHere = context->find(from, lookHere))
          != string::npos) {
        context->replace(foundHere, from.size(), to);
        lookHere = foundHere + to.size();
    }
    return context;
}