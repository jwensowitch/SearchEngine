//
//  LList.h
//  Wensowitch_Project4
//
//  Created by Admin on 11/4/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

//
//LList Class Adapted from http://www.geeksforgeeks.org/graph-and-its-representations/
//

#ifndef Wensowitch_Project4_LList_h
#define Wensowitch_Project4_LList_h

#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack.h"

class LList
{
    
private:
    int Hubs;
    
    class Node
    {
    public:
        int dest;
        Node* next;
        ~Node()
        {

        }
    };
    
    class List
    {
    public:
        Node* head;
    };
    
    List* arrayList;
    Stack* flights;
    Stack* path;
    
public:
    LList(int HubCount) : Hubs(HubCount)
    {
        arrayList = new List[Hubs];
        flights = new Stack(100);
        path = new Stack(100);

        for (int i = 0; i < Hubs; ++i)
        {
            arrayList[i].head = NULL;
        }
    }
    
    ~LList()
    {
        delete [] arrayList;
        delete flights;
        delete path;

    }
    
    Node* branchListNode(int dest)
    {
        Node* addNode = new Node;
        addNode->dest = dest;
        addNode->next = NULL;

        return addNode;
    }

    //Iterative Backtracking
    int* solve(int start, int end)
    {
        int s = start;
        
        Node* travel = arrayList[s].head;
        
        path->push(s);
        
        if(start == -1 || end == -1)    //invalid location
        {
            return NULL;
        }
        
        if(travel == NULL)  //no dest from starting source
        {
            return NULL;
        }
        
        while(true)
        {
            if(travel != NULL)  //grab location
            {
                path->push(travel->dest);
                
                flights->push(travel->dest);
                
                travel = travel->next;
            }
            if(path->peek() == end) //check if source path == dest
            {
                return (path->retArr());
                
            }
            else if (travel == NULL)    //if reached end of current list
            {
                travel = arrayList[flights->peek()].head;
                path->pop();
                path->push(flights->pop());
            }
            else    //remove most recent if not dest
            {
                path->pop();
            }
        }

        return (path->retArr());

    }
    
    
    int getPathSize()
    {
        return path->size();
    }
    
    
    void print_hCount()
    {
        cout << "flights: ";
        flights->display();
        cout << "path: ";
        path->display();
    }
    
    
    void addEdge(int src, int dest)
    {
        Node* addNode = branchListNode(dest);
        addNode = branchListNode( src );
        addNode->next = arrayList[ dest ].head;
        arrayList[ dest ].head = addNode;
    }

    
    void printGraph()
    {
        int i;
        for(i = 0; i< Hubs; ++i)
        {
            Node * travel = arrayList[i].head;
            cout << "\n List of " << i << "\n head ";
            while(travel)
            {
                cout << "-> " << travel->dest;
                travel = travel->next;
            }
            cout << endl;
        }
    }
};

#endif
