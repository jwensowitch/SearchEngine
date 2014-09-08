#ifndef TEAM_H
#define TEAM_H

//
//  Team.h
//  lasertag
//
//

#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

class Team {

public:
    Team(char *file_name);
    ~Team();
    int processScore(int**, int);
    void printTags(const Team&, int**, string, char*);
    void sortArrays();
    void testPrint();
protected:
    char* file;
    string name;
    int size;
    int* numbers;
    string* members;
    int* member_tags;
    int* member_scores;
    int score;

};

#endif // TEAM_H
