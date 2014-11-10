//
//  Stack.h
//  Wensowitch_Project4
//
//  Created by Admin on 11/6/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//


//
//Stack Class Adapted from http://gauss.ececs.uc.edu/Courses/C321/html/stack++.html
//
#ifndef Wensowitch_Project4_Stack_h
#define Wensowitch_Project4_Stack_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Stack
{
public:
    friend class LList;
    
    Stack(int num) {  top = 0; maxelem = num; s = new int[maxelem]; }
    
    ~Stack()
    {
        delete [] s;
    }
    
    void  push(int t)
    {
        if (top == maxelem) return;
        s[top++] = t;
    }
    
    int pop()
    {
        if (top == 0) return -1;
        return s[--top];
    }
    
    int peek()
    {
        int t;
        if(top == 0) return -1;
        t = top - 1;
        return s[t];
    }
    
    int size()
    {
        return top;
    }
    
    int* retArr()
    {
        return s;
    }
    
    void display()
    {
        if (top == 0) { cout << "(empty)\n";  return; }
        for (int t=0 ; t < top ; t++) cout << s[t] << " ";
        cout << "\n";
    }
    
    
    int   empty()  {  return top == 0;  }

private:
    
    int *s;
    int top;
    int maxelem;
};



#endif
