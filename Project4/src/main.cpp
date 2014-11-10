//
//  main.cpp
//  Wensowitch_Project4
//
//  Created by Admin on 10/23/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "LList.h"
#include "Stack.h"

using namespace std;


int main(int argc, const char * argv[])
{
    
    ifstream flightData(argv[1]);
    ifstream flightPlan(argv[2]);
    int dataLines;
    int numFlightPlans;
    
    int* index;
    int* flights;
    int** finalPath = nullptr;
    string* indexVal;
    string* data;
    string temp;
    
    
    flightPlan >> numFlightPlans;
    flightPlan.ignore();
    
    flightData >> dataLines;
    flightData.ignore();
    
    const int dataPoints = dataLines*3;
    const int flightPoints = numFlightPlans*2;
    
    
    data = new string[dataPoints];
    index = new int[dataPoints];
    int indi = 0;
    indexVal = new string[dataPoints];
    flights = new int[flightPoints];
    
    
    //Initilizer
    for(int i = 0; i < dataPoints; ++i)
    {
        data[i] = "";
        index[i] = i;
        indexVal[i] = "";
    }
    
    for(int i = 0; i < flightPoints; ++i)
    {
        flights[i] = -1;
    }
    
    
    //data, index, indexVal
    for (int i = 0; i < dataPoints; ++i)
    {
        int j;
        bool dup = false;
        getline(flightData, temp, ','); //source
        flightData.ignore();
        
        for(j = 0; j < dataPoints; ++j)
        {
            if(temp.compare(indexVal[j]) == 0)
                dup = true;
        }
        
        if(dup == true) //remove repeats
        {}
        else
        {
            indexVal[indi] = temp;
            indi++;
        }
        
        dup = false;
        data[i] = temp;
        i++;
        getline(flightData, temp, ','); //dest
        flightData.ignore();
        
        for(j = 0; j < dataPoints; ++j)
        {
            if(temp.compare(indexVal[j]) == 0)
                dup = true;
        }
        
        if(dup == true) //remove repeats
        {}
        else
        {
            indexVal[indi] = temp;
            indi++;
        }
        
        data[i] = temp;
        i++;
        
        getline(flightData, temp); //cost
        data[i] = temp;
        
    }
    flightData.close();
    
    
    //flights
    for(int i = 0; i < flightPoints; ++i)
    {
        getline(flightPlan, temp, ','); //source
        flightPlan.ignore();
        for(int j = 0; j < indi; ++j)
        {
            if(temp.compare(indexVal[j]) == 0)
            {
                flights[i] = index[j];
            }
        }
        
        i++;
        
        getline(flightPlan, temp);  //dest
        for(int j = 0; j < indi; ++j)
        {
            if(temp.compare(indexVal[j]) == 0)
            {
                flights[i] = index[j];
            }
        }
    }
    flightPlan.close();
    
    
    //Linked List Construction
    LList* dest[numFlightPlans];
    
    for(int i = 0; i < numFlightPlans; ++i)
    {
        dest[i] = new LList(indi);
    }
    
    for (int i = 0; i < dataPoints; ++i)
    {
        int j, k;
        
        for(j = 0; j < indi; ++j)
        {
            if(data[i].compare(indexVal[j]) == 0)
            {
                break;
            }
        }
        
        ++i;
        
        for(k = 0; k < indi; ++k)
        {
            if(data[i].compare(indexVal[k]) == 0)
            {
                break;
            }
        }
        
        for(int l = 0; l < numFlightPlans; ++l)
        {
            dest[l]->addEdge(k,j);
        }
        
        ++i;
    }
    
    
    //Solving Path
    finalPath = new int*[numFlightPlans];
    
    for(int l = 0; l < numFlightPlans; ++l)
    {
        //dest[l]->printGraph(); cout << endl << endl;
        finalPath[l] = new int[indi]();
    }
    
    for(int i = 0, j = 0; i < numFlightPlans; ++i)
    {
        finalPath[i] = dest[i]->solve(flights[j],flights[j+1]);
        j+=2;
    }
    
    
    //print solution
    ofstream output(argv[3]);
    for(int i = 0, l = 0; i < numFlightPlans; ++i)
    {
        int totalCost = 0;
        
        output << "Flight " << i+1 <<": ";
        if (flights[l] == -1)
        {
            output << "Invalid Location to ";
        }
        else
            output << indexVal[flights[l]] << " to ";
        
        l++;
        
        if (flights[l] == -1)
        {
            output << "Invalid Location" << endl;
        }
        else
            output << indexVal[flights[l]] << endl;
        
        l++;
        
        
        if(finalPath[i] == NULL)
        {
            output << "Not Possible" << endl;
        }
        else
        {
            int iter;
            
            if(dest[i]->getPathSize() == 2)
            {
                iter = 1;
            }
            else
                iter = dest[i]->getPathSize()/2+1;
            
            
            for(int j = 0; j < iter; ++j)
            {
                output << "Leg " << j+1 << ":" << endl;
                
                output << indexVal[finalPath[i][j]] << " -> "
                << indexVal[finalPath[i][j+1]] << " ";
                
                
                for(int k = 0, m = 1; k < dataPoints || m < dataPoints; k+=3, m+=3)
                {
                    if (indexVal[finalPath[i][j]].compare(data[k]) == 0 &&
                        indexVal[finalPath[i][j+1]].compare(data[m]) == 0)
                    {
                        output << "$" << data[m+1] << endl;
                        totalCost += (stoi(data[m+1]));
                    }
                }
            }
            output << "\nTotal Cost: $" << totalCost << endl << endl;
        }
        output << endl << endl;
    }
    
    //Delete Dynamic
    delete [] data;
    delete [] index;
    delete [] indexVal;
    delete [] flights;
    for(int i = 0; i < numFlightPlans; ++i)
    {
        delete dest[i];

    }
    delete [] finalPath;
    
    return 0;
}





