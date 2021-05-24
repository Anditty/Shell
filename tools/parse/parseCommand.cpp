//
// Created by edison on 2021/5/13.
//
#include "parseCommand.h"

char **split_command(const string &command) {
    vector<string> array;
    stringstream ss(command);
    string temp;

    while (ss >> temp)
        array.push_back(temp);
    char **args = new char *[array.size() + 1];
    for (int i = 0; i < array.size(); ++i) {
        args[i] = (char *) array.at(i).c_str();
    }
    args[array.size()] = nullptr;

    return args;
}

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
