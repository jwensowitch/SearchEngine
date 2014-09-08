
//
//  Team.cpp
//  lasertag
//


#include "Team.h"

Team::Team(char* file_name) {
    score = 0;
    file = file_name;
    ifstream temp(file);
    if (!temp) {
        cout << "Couldn't open Team Files" << endl;
        exit(1);
    }
    getline(temp, name);
    temp >> size;
    temp.ignore();
    numbers = new int[size];    //dynamic parallel arrays for match info
    members = new string[size];
    member_tags = new int[size];
    member_scores = new int[size];
    for( int i = 0; i < size; ++i) {    //reading in names
        temp >> numbers[i];
        getline(temp, members[i]);
    }
    for( int i = 0; i < size; ++i) {
        member_tags[i] = 0;
        member_scores[i] = 0;
    }

}

int Team::processScore(int** arr, int tags) {
    for(int x = 0; x < size; ++x) {
        for(int i = 0; i < tags; ++i){
            if(arr[i][0] == numbers[x]) {
                member_tags[x] += 1;
                switch (arr[i][3]) {
                        case 1:
                            member_scores[x] += 5;
                            break;
                        case 2:
                             member_scores[x] += 8;
                            break;
                        case 3:
                             member_scores[x] += 10;
                            break;
                        case 4:
                             member_scores[x] += 15;
                        default:
                            break;
                    }
            }

        }
    }
    for (int i = 0; i < size; i++) {
        score += member_scores[i];
    }
    return score;
}

void Team::printTags(const Team& t, int** arr, string verb, char* out) {
    ofstream output;
    output.open(out);   //opening file for output
    string winner = " ";
    string team1, team2 = " ";
    string* members1_arr;
    string* members2_arr;
    int* tags1_arr;
    int* tags2_arr;
    int* score1_arr;
    int* score2_arr;
    int* nums1;
    int* nums2;
    int team1_score = 0, team2_score = 0, team1_size = 0, team2_size = 0, temp = 0, total_tags = 0;
    if (t.name < name) {    //handles teams alphabetically
        team1 = t.name;
        team2 = name;
        nums1 = t.numbers;
        nums2 = numbers;
        team1_score = t.score;
        team2_score = score;
        team1_size = t.size;
        team2_size = size;
        members1_arr = t.members;
        members2_arr = members;
        tags1_arr = t.member_tags;
        tags2_arr = member_tags;
        score1_arr = t.member_scores;
        score2_arr = member_scores;
    }
    else {
        team1 = name;
        team2 = t.name;
        nums1 = numbers;
        nums2 = t.numbers;
        team1_score = score;
        team2_score = t.score;
        team1_size = size;
        team2_size = t.size;
        members1_arr = members;
        members2_arr = t.members;
        tags1_arr = member_tags;
        tags2_arr = t.member_tags;
        score1_arr = member_scores;
        score2_arr = t.member_scores;
    }

    for(int i = 0; i < team1_size; ++i) {
        total_tags += tags1_arr[i];
    }
    for(int i = 0; i < team2_size; ++i) {
        total_tags += tags2_arr[i];
    }

    if(team1_score > team2_score) {
        winner = team1;
    }
    else
        winner = team2;

    if(verb == "vlow") {

            output << team1 << ": " << team1_score << " points" << endl;
            output << team2 << ": " << team2_score << " points" << endl;

        output << "Overall Winners: " << winner << endl;
    }

    else if(verb == "vmed") {
            output << team1 << endl;
            for(int i = 0; i < team1_size; ++i){
                output << "   " << members1_arr[i] << " had a total of " << tags1_arr[i] << " tags" << endl;
            }
        output << endl;
        output << team2 << endl;
        for(int i = 0; i < team1_size; ++i){
                output << "    " << members2_arr[i] << " had a total of " << tags2_arr[i] << " tags" << endl;
    }
        output << endl;
        int max = score1_arr[0];
        int maxi = 0;
        for(int i = 0; i < size; ++i) {
            if(score1_arr[i] > max) {
                maxi = i;
            }
        }
        output << "Best score from " << team1 << ": " << members1_arr[maxi] << " (" << score1_arr[maxi] << " points)" << endl;
        max = score2_arr[0];
        maxi = 0;
        for(int i = 0; i < size; i++) {
            if(score2_arr[i] > max) {
                maxi = i;
            }
        }
        output << "Best score from " << team2 << ": " << members2_arr[maxi] << " (" << score2_arr[maxi] << " points)" << endl;
        output << team1 << ": " << team1_score << " points" << endl;
        output << team2 << ": " << team2_score << " points" << endl;
        output << "Overall Winners: " << winner << endl;

    }
    else if (verb == "vhigh") {
        output << team1 << endl;
        for(int i = 0; i < team1_size; ++i){
            for(int j = 0; j < team2_size; ++j) {
                temp = 0;
                for (int k = 0; k < total_tags; ++k) {
                    if(arr[k][0] == nums1[i] && arr[k][1] == nums2[j])  //temp tracks number of times each teamA member
                        temp++;                                         //tags a teamB member and vice versa
                }
                output << "   " << members1_arr[i] << " tagged " << members2_arr[j] << " " << temp << " times" << endl;
            }
            output << "   " << members1_arr[i] << " had a total of " << tags1_arr[i] << " tags" << endl;
        }
        output << team1 << ": " << team1_score << " points\n" << endl;

        output << team2 << endl;
        for(int i = 0; i < team2_size; ++i){
            for(int j = 0; j < team1_size; ++j) {
                temp = 0;
                for (int k = 0; k < total_tags; ++k) {
                    if(arr[k][0] == nums2[i] && arr[k][1] == nums1[j])
                        temp++;
                }
                output << "   " << members2_arr[i] << " tagged " << members1_arr[j] << " " << temp << " times" << endl;
            }
            output << "   " << members2_arr[i] << " had a total of " << tags2_arr[i] << " tags" << endl;
        }
        output << team2 << ": " << team2_score << " points\n" << endl;

        output << "Winners: " << winner << endl;
    }

else {

    output << "Not Valid Verbosity!" << endl;
    }

    output.close(); //closing output file
}

void Team::sortArrays(){
        int i, j, t, n, s;
        string m;
        for(i = 0; i < size; ++i)
        {
            for(j = i+1; j < size; ++j)
            {
                if(member_tags[j] > member_tags[i])     //sort members by most tags
                {
                    t = member_tags[i];     //storage for swap sort method
                    m = members[i];
                    n = numbers[i];
                    s = member_scores[i];
                    member_tags[i] = member_tags[j];
                    members[i] = members[j];
                    numbers[i] = numbers[j];
                    member_scores[i] = member_scores[j];
                    member_tags[j] = t;
                    members[j] = m;
                    numbers[j] = n;
                    member_scores[j] = s;

                }
            }
        }


}

void Team::testPrint() {
    for( int i = 0; i < size; i++) {
        cout << numbers[i] << " " << members[i] << " " << member_tags[i] << " " << member_scores[i] << endl;
    }
    cout << endl;
}

Team::~Team() {     //destructor to handle dynamic memory allocation
    delete [] numbers;
    delete [] members;
    delete [] member_tags;
    delete [] member_scores;
}
