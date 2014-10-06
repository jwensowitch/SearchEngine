//  **Group Project**
//  Partner: Eric Hawkins
//
//  Wensowitch_Project3
//
//
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "SortingCompetition.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    SortingCompetition* f = new SortingCompetition(argv[1]);
    f->setFileName(argv[1]);
    f->readData();
    f->prepareData();

    start = std::chrono::system_clock::now();
    f->sortData();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " <<
    std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
    f->outputData(argv[2]);
    delete f;
}


