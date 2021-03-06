//
// Created by edison on 2021/5/13.
//
#include "parseCommand.h"


int find_pipe(char **command) {
    for (int i = 0; command[i] != nullptr; ++i) {
        if (strcmp(command[i], "|") == 0) {
            return i;
        }
    }

    return -1;
}

int find_question(char **command) {
    for (int i = 0; command[i] != nullptr; ++i) {
        if (strcmp(command[i], "?") == 0) {
            return i;
        }
    }

    return -1;
}

int find_split(char **command, char *s){
    for (int i = 0; command[i] != nullptr; ++i) {
        if (strcmp(command[i], s) == 0) {
            return i;
        }
    }

    return -1;
}

vector<int> find_all_target_position(const string& s, const string& target){
    vector<int> result;
    size_t position=0;
    while((position=s.find(target,position))!=string::npos)
    {
        result.push_back((int )position);
        position += target.length();
    }

    return result;
}
