#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Team.h"

using namespace std;

int** readMatch(char*, int&);

int main(int argc, char* argv[]){
    int tags; //
    int** temp = readMatch(argv[3], tags);

    Team teamA(argv[1]);
    Team teamB(argv[2]);

    teamA.processScore(temp, tags);
    teamB.processScore(temp, tags);

    teamA.sortArrays();
    teamB.sortArrays();

    teamB.printTags(teamA, temp, argv[5], argv[4]);

    return 0;
}

int** readMatch(char* file, int& t) {
    ifstream matchInput(file);
if (!matchInput) {
    cout << "Couldn't open file Match File" << endl;
    exit(1);
}
    int tags;
    matchInput >> tags;
    t = tags;
    matchInput.ignore();
    int** tag_info = new int*[tags];    //delete after use

    for (int i = 0; i < tags; ++i) {
        tag_info[i] = new int[4];
    }

    for(int i = 0; i < tags; ++i){
        for (int j = 0; j < 4; ++j) {
            matchInput >> tag_info[i][j];
        }
    }

    matchInput.close();

    return tag_info;
}
