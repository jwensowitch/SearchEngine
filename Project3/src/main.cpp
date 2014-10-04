//
//  main.cpp
//  Wensowitch_Project3
//
//  Created by Admin on 10/1/14.
//  Copyright (c) 2014 Admin. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
//#include <pthread.h>
#include "SortingCompetition.h"

using namespace std;

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    SortingCompetition* f = new SortingCompetition("lessbig.txt");
    //f->setFileName("test.txt");
    f->readData();
    f->prepareData();

    start = std::chrono::system_clock::now();
    f->sortData();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " <<
    std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
    f->outputData("output.txt");
}

/*
long fibonacci(int n)
{
    if (n < 3) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, const char * argv[])
{

    

        //declare 2 time points
        std::chrono::time_point<std::chrono::system_clock> start, end;
        
        //store the current time (now()) in start, execute
        //Fibonacci function, then store current time in end
        start = std::chrono::system_clock::now();
        std::cout << "f(42) = " << fibonacci(42) << '\n';
        end = std::chrono::system_clock::now();
        
        //subtract end from beginning to get number of seconds elapsed
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time =
        std::chrono::system_clock::to_time_t(end);
        
        //output the duration.
        std::cout << "finished computation at " <<
        std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return 0;
}
*/
